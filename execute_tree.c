/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:48:58 by mratke            #+#    #+#             */
/*   Updated: 2025/02/22 17:43:49 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	l_redirect(t_vars *vars, t_node *node)
{
	node->new_fds[0] = open(node->command_args[1], O_RDONLY);
	if (node->new_fds[0] == -1)
		return (perror(node->command_args[0]), errno);
	else
	{
		dup2(node->new_fds[0], STDIN_FILENO);
		close_fds(&(node->new_fds));
		if (execute_node(vars, node->left))
			return (ERR_SYNTAX);
	}
	restore_fds(&(node->old_fds));
	return (0);
}

static int	ll_redirect(t_vars *vars, t_node *node)
{
	char	expans;

	expans = 0;
	if (vars->im_in_pipe)
		reset_stdio(vars);
	if ((ft_strchr((node->command_args)[1], '\'') == 0
		&& ft_strchr((node->command_args)[1], '"') == 0))
	{
		printf("Expans\n");
		expansion(vars, node->command_args);
		expans = 1;
	}
	here_doc(vars, node, expans);
	restore_fds(&(node->old_fds));
	write_list_to_fd(vars->here_doc_buf, STDOUT_FILENO);
	free_list(&(vars->here_doc_buf));
	return (0);
}

static int	r_redirect(t_vars *vars, t_node *node)
{
	node->new_fds[1] = open(node->command_args[1], O_CREAT | O_TRUNC | O_WRONLY,
			0644);
	if (node->new_fds[1] == -1)
		perror(node->command_args[1]);
	else
	{
		dup2(node->new_fds[1], STDOUT_FILENO);
		close_fds(&(node->new_fds));
		if (execute_node(vars, node->left))
			return (ERR_SYNTAX);
	}
	restore_fds(&(node->old_fds));
	return (0);
}

static int	rr_redirect(t_vars *vars, t_node *node)
{
	node->new_fds[1] = open(node->command_args[1],
			O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (node->new_fds[1] == -1)
		perror(node->command_args[1]);
	else
	{
		dup2(node->new_fds[1], STDOUT_FILENO);
		close_fds(&(node->new_fds));
		if (execute_node(vars, node->left))
			return (ERR_SYNTAX);
	}
	restore_fds(&(node->old_fds));
	return (0);
}

static int	pipe_redirect(t_vars *vars, t_node *node)
{
	save_fds(&(node->old_fds));
	if (create_pipe(&(node->new_fds)) < 0)
	{
		restore_fds(&(node->old_fds));
		close_fds(&(node->new_fds));
		return (77);
	}
	dup2(node->new_fds[1], STDOUT_FILENO);
	close(node->new_fds[1]);
	vars->im_in_pipe = 1;
	if (execute_node(vars, node->left))
	{
		restore_fds(&(node->old_fds));
		close_fds(&(node->new_fds));
		return (ERR_SYNTAX);
	}
	dup2(node->old_fds[1], STDOUT_FILENO);
	close(node->old_fds[1]);
	dup2(node->new_fds[0], STDIN_FILENO);
	close(node->new_fds[0]);
	vars->im_in_pipe = 1;
	if (execute_node(vars, node->right))
	{
		restore_fds(&(node->old_fds));
		close_fds(&(node->new_fds));
		return (ERR_SYNTAX);
	}
	dup2(node->old_fds[0], STDIN_FILENO);
	close(node->old_fds[0]);
	vars->im_in_pipe = 0;
	// restore_fds(&(node->old_fds));
	return (0);
}

int	execute_node(t_vars *vars, t_node *node)
{
	if (!node)
		return (0);
	if (!(node->type == REDIRECT_TYPE)
		&& (ft_strcmp("<<", node->command_args[0]) != 0))
		expansion(vars, node->command_args);
	if (node->type == COMMAND_TYPE)
	{
		if (node->command_args == NULL)
			return (ERR_SYNTAX);
		execute_command(vars, node, node->command_args);
	}
	else if (node->type == REDIRECT_TYPE)
	{
		save_fds(&(node->old_fds));
		if (ft_strcmp("<", node->command_args[0]) == 0)
			l_redirect(vars, node);
		else if (ft_strcmp(">", node->command_args[0]) == 0)
			r_redirect(vars, node);
		else if (ft_strcmp(">>", node->command_args[0]) == 0)
			rr_redirect(vars, node);
		else if (ft_strcmp("<<", node->command_args[0]) == 0)
			ll_redirect(vars, node);
	}
	else if (node->type == PIPE_TYPE)
		pipe_redirect(vars, node);
	// || является логическим «ИЛИ» и выполнит вторую часть оператора,
	// только если первая часть не верна;
	else if (node->type == OR_TYPE)
	{
		if (execute_node(vars, node->left))
			return (ERR_SYNTAX);
		wait_childs(vars);
		if (vars->return_code != 0)
			if (execute_node(vars, node->right))
				return (ERR_SYNTAX);
	}
	// && является логическим «И» и выполнит вторую часть оператора
	// только в том случае, если первая часть верна.
	else if (node->type == AND_TYPE)
	{
		if (execute_node(vars, node->left))
			return (ERR_SYNTAX);
		wait_childs(vars);
		if (vars->return_code == 0)
			if (execute_node(vars, node->right))
				return (ERR_SYNTAX);
	}
	return (0);
}

int	execute_tree(t_vars *vars, char *cmnd)
{
	// struct termios	term1;
	// printf("Execute command: %s\n", cmnd);
	vars->tokens = tokenize(vars, cmnd);
	if (ft_lstsize(vars->tokens) < 1)
		return (free_list(&(vars->tokens)), 0);
	printf("Print tokens list:\n");
	print_list(vars->tokens);
	add_history(cmnd);
	vars->node_list = parse_tokens(&(vars->tokens));
	printf("Print tree\n");
	print_tree(vars->node_list, 0);
	// printf("Execute tree\n");
	if (execute_node(vars, vars->node_list))
		return (error_message(NULL, ERR_SYNTAX), ERR_SYNTAX);
	wait_childs(vars);
	reset_vars(vars);
	return (0);
}
