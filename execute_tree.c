/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:48:58 by mratke            #+#    #+#             */
/*   Updated: 2025/02/14 16:42:50 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_node(t_vars *vars, t_node *node)
{
	int		tmpint;

	tmpint = 0;
	if (!node)
		return ;
	if (node->type == COMMAND_TYPE)
	{
		vars->cmnd_nmbrs++;
		tmpint = execute_command(vars, node, node->command_args);
		if (vars->return_code == 0)
			vars->return_code = tmpint;
	}
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
			node->new_fds[1] = open(node->command_args[1], O_CREAT
					| O_TRUNC | O_WRONLY, 0644);
			dup2(node->new_fds[1], STDOUT_FILENO);
		}
		else if (ft_strcmp(">>", node->command_args[0]) == 0)
		{
			node->new_fds[1] = open(node->command_args[1], O_CREAT
					| O_APPEND | O_WRONLY, 0644);
			dup2(node->new_fds[1], STDOUT_FILENO);
		}
		// HEREDOC
		// else if (ft_strcmp("<<", node->command_args[0]) == 0)
		// {
		// 	node->new_fds[1] = open(node->command_args[1], O_CREAT
		// 			| O_APPEND | O_WRONLY, 0644);
		// 	dup2(node->new_fds[1], STDOUT_FILENO);
		// }
		close_fds(&(node->new_fds));
		execute_node(vars, node->left);
		restore_fds(&(node->old_fds));
	}
	else
	{
		// printf("Operator: %s\n",
		// 	node->type == PIPE_TYPE ? "PIPE" : node->type == AND_TYPE ? "AND" : "OR");
		if (node->type == PIPE_TYPE)
		{
			save_fds(&(node->old_fds));
			create_pipe(&(node->new_fds));
			dup2(node->new_fds[1], STDOUT_FILENO);
			close(node->new_fds[1]);
			execute_node(vars, node->left);
			// close(STDOUT_FILENO);
			dup2(node->old_fds[1], STDOUT_FILENO);
			dup2(node->new_fds[0], STDIN_FILENO);
			close(node->new_fds[0]);
			execute_node(vars, node->right);
			restore_fds(&(node->old_fds));
		}
		// || является логическим «ИЛИ» и выполнит вторую часть оператора,
		// только если первая часть не верна;
		else if (node->type == OR_TYPE)
		{
			execute_node(vars, node->left);
			wait_childs(&(vars->cmnd_nmbrs));
			if (vars->return_code != 0)
				execute_node(vars, node->right);
		}
		// && является логическим «И» и выполнит вторую часть оператора
		// только в том случае, если первая часть верна.
		else if (node->type == AND_TYPE)
		{
			execute_node(vars, node->left);
			wait_childs(&(vars->cmnd_nmbrs));
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
	printf("Print tokens list:\n");
	print_list(vars->tokens);
	add_history(cmnd);
	vars->node_list = parse_tokens(&(vars->tokens));
	// printf("Print tree\n");
	// print_tree(vars->node_list, 0);
	// printf("Execute tree\n");
	// save_fds(&(vars->old_fds));
	// tcgetattr(STDIN_FILENO, &term1);
	// term1.c_lflag &= ~ECHO;
	// tcsetattr(STDIN_FILENO, 0, &term1);
	execute_node(vars, vars->node_list);
	wait_childs(&(vars->cmnd_nmbrs));
	// term1.c_lflag |= ECHO;
	// tcsetattr(STDIN_FILENO, 0, &term1);
	// restore_fds(&(vars->old_fds));
	// execute_programm(vars, cmnd);
	reset_vars(vars);
	return (0);
}
