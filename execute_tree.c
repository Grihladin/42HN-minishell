/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:48:58 by mratke            #+#    #+#             */
/*   Updated: 2025/02/15 12:53:03 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_node(t_vars *vars, t_node *node)
{
	if (!node)
		return ;
	if (node->type == COMMAND_TYPE)
		execute_command(vars, node, node->command_args);
	else if (node->type == REDIRECT_TYPE)
	{
		save_fds(&(node->old_fds));
		if (ft_strcmp("<", node->command_args[0]) == 0)
		{
			node->new_fds[0] = open(node->command_args[1], O_RDONLY);
			dup2(node->new_fds[0], STDIN_FILENO);
		}
		else if (ft_strcmp(">", node->command_args[0]) == 0)
		{
			node->new_fds[1] = open(node->command_args[1],
					O_CREAT | O_TRUNC | O_WRONLY, 0644);
			dup2(node->new_fds[1], STDOUT_FILENO);
		}
		else if (ft_strcmp(">>", node->command_args[0]) == 0)
		{
			node->new_fds[1] = open(node->command_args[1],
					O_CREAT | O_APPEND | O_WRONLY, 0644);
			dup2(node->new_fds[1], STDOUT_FILENO);
		}
		// HEREDOC
		else if (ft_strcmp("<<", node->command_args[0]) == 0)
		{
			create_pipe(&(node->new_fds));
			dup2(node->new_fds[1], STDOUT_FILENO);
			close(node->new_fds[1]);
			here_doc_fork(vars, node, node->command_args);
			dup2(node->old_fds[1], STDOUT_FILENO);
			dup2(node->new_fds[0], STDIN_FILENO);
			close(node->new_fds[0]);
		}
		close_fds(&(node->new_fds));
		execute_node(vars, node->left);
		restore_fds(&(node->old_fds));
		close_fds(&(node->old_fds));
	}
	else
	{
		// 	node->type == PIPE_TYPE ? "PIPE" : node->type == AND_TYPE ? "AND" : "OR");
		if (node->type == PIPE_TYPE)
		{
			save_fds(&(node->old_fds));
			create_pipe(&(node->new_fds));
			dup2(node->new_fds[1], STDOUT_FILENO);
			close(node->new_fds[1]);
			execute_node(vars, node->left);
			dup2(node->old_fds[1], STDOUT_FILENO);
			dup2(node->new_fds[0], STDIN_FILENO);
			close(node->new_fds[0]);
			execute_node(vars, node->right);
			restore_fds(&(node->old_fds));
			close_fds(&(node->old_fds));
		}
		// || является логическим «ИЛИ» и выполнит вторую часть оператора,
		// только если первая часть не верна;
		else if (node->type == OR_TYPE)
		{
			execute_node(vars, node->left);
			wait_childs(vars);
			if (vars->return_code != 0)
				execute_node(vars, node->right);
		}
		// && является логическим «И» и выполнит вторую часть оператора
		// только в том случае, если первая часть верна.
		else if (node->type == AND_TYPE)
		{
			execute_node(vars, node->left);
			wait_childs(vars);
			if (vars->return_code == 0)
				execute_node(vars, node->right);
		}
	}
}

int	execute_tree(t_vars *vars, char *cmnd)
{
	// struct termios	term1;
	// printf("Execute command: %s\n", cmnd);
	vars->tokens = tokenize(vars, cmnd);
	if (ft_lstsize(vars->tokens) < 1)
		return (free_list(&(vars->tokens)), 0);
	// printf("Print tokens list:\n");
	// print_list(vars->tokens);
	add_history(cmnd);
	vars->node_list = parse_tokens(&(vars->tokens));
	// printf("Print tree\n");
	// print_tree(vars->node_list, 0);
	// printf("Execute tree\n");
	execute_node(vars, vars->node_list);
	wait_childs(vars);
	reset_vars(vars);
	return (0);
}
