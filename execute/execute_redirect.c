/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:56:01 by psenko            #+#    #+#             */
/*   Updated: 2025/02/27 19:07:17 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	l_redirect(t_vars *vars, t_node *node)
{
	node->new_fds[0] = open(node->command_args[1], O_RDONLY);
	if (node->new_fds[0] == -1)
	{
		restore_fds(&(node->old_fds));
		vars->return_code = 1;
		return (perror(node->command_args[1]), 0);
	}
	else
	{
		dup2(node->new_fds[0], STDIN_FILENO);
		close_fds(&(node->new_fds));
		if (execute_node(vars, node->left))
			return (restore_fds(&(node->old_fds)), ERR_SYNTAX);
	}
	restore_fds(&(node->old_fds));
	return (0);
}

int	ll_redirect(t_vars *vars, t_node *node)
{
	char	expans;

	expans = 0;
	if (ft_strlen((node->command_args)[1]) < 1)
		return (error_message(node, 258), 258);
	if (vars->im_in_pipe)
		reset_stdio(vars);
	if ((ft_strchr((node->command_args)[1], '\'') == 0
		&& ft_strchr((node->command_args)[1], '"') == 0))
		expans = 1;
	(node->command_args)[1] = delete_quotes((node->command_args)[1]);
	return (here_doc(vars, node, expans));
}

int	r_redirect(t_vars *vars, t_node *node)
{
	node->new_fds[1] = open(node->command_args[1], O_CREAT | O_TRUNC | O_WRONLY,
			0644);
	if (node->new_fds[1] == -1)
	{
		vars->return_code = 1;
		restore_fds(&(node->old_fds));
		return (perror(node->command_args[1]), 1);
	}
	else
	{
		dup2(node->new_fds[1], STDOUT_FILENO);
		close_fds(&(node->new_fds));
		execute_node(vars, node->left);
	}
	restore_fds(&(node->old_fds));
	return (0);
}

int	rr_redirect(t_vars *vars, t_node *node)
{
	node->new_fds[1] = open(node->command_args[1],
			O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (node->new_fds[1] == -1)
	{
		restore_fds(&(node->old_fds));
		vars->return_code = 1;
		return (perror(node->command_args[1]), 1);
	}
	else
	{
		dup2(node->new_fds[1], STDOUT_FILENO);
		close_fds(&(node->new_fds));
		if (execute_node(vars, node->left))
			return (restore_fds(&(node->old_fds)), ERR_SYNTAX);
	}
	restore_fds(&(node->old_fds));
	return (0);
}

int	execute_redirect(t_vars *vars, t_node *node)
{
	if ((node->command_args)[1] == NULL)
		return (vars->return_code = 2, error_message(node, 258), 258);
	save_fds(&(node->old_fds));
	if (ft_strcmp("<", node->command_args[0]) == 0)
		l_redirect(vars, node);
	else if (ft_strcmp(">", node->command_args[0]) == 0)
		r_redirect(vars, node);
	else if (ft_strcmp(">>", node->command_args[0]) == 0)
		rr_redirect(vars, node);
	else if (ft_strcmp("<<", node->command_args[0]) == 0)
		ll_redirect(vars, node);
	return (0);
}
