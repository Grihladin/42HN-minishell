/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:53:20 by psenko            #+#    #+#             */
/*   Updated: 2025/02/27 19:07:14 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	pipe_redirect_p2(t_vars *vars, t_node *node)
{
	dup2(node->new_fds[1], STDOUT_FILENO);
	close(node->new_fds[1]);
	vars->im_in_pipe = 1;
	if (execute_node(vars, node->left))
	{
		restore_fds(&(node->old_fds));
		vars->im_in_pipe = 0;
		return (close_fds(&(node->new_fds)), ERR_SYNTAX);
	}
	dup2(node->old_fds[1], STDOUT_FILENO);
	close(node->old_fds[1]);
	dup2(node->new_fds[0], STDIN_FILENO);
	close(node->new_fds[0]);
	vars->im_in_pipe = 1;
	if (execute_node(vars, node->right))
	{
		restore_fds(&(node->old_fds));
		vars->im_in_pipe = 0;
		return (close_fds(&(node->new_fds)), ERR_SYNTAX);
	}
	dup2(node->old_fds[0], STDIN_FILENO);
	return (0);
}

int	pipe_redirect(t_vars *vars, t_node *node)
{
	if ((node->left == NULL) || (node->right == NULL)
		|| ((node->left->type != PIPE_TYPE)
			&& (node->left->command_args == NULL))
		|| ((node->right->type != PIPE_TYPE)
			&& (node->right->command_args == NULL)))
		return (error_message(node, 258), 258);
	save_fds(&(node->old_fds));
	if (create_pipe(&(node->new_fds)) < 0)
	{
		restore_fds(&(node->old_fds));
		return (77);
	}
	if (pipe_redirect_p2(vars, node) != 0)
		return (ERR_SYNTAX);
	close(node->old_fds[0]);
	vars->im_in_pipe = 0;
	return (0);
}
