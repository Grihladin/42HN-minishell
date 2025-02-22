/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:17:27 by psenko            #+#    #+#             */
/*   Updated: 2025/02/22 09:21:42 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_lvl(t_env_list **env_list)
{
	t_env_list	*node;
	char		*value;
	int			lvl;

	node = *env_list;
	while (node)
	{
		if (!ft_strcmp(node->key, "SHLVL"))
		{
			lvl = ft_atoi(node->value);
			lvl++;
			value = ft_itoa(lvl);
			free(node->value);
			node->value = value;
			break ;
		}
		node = node->next;
	}
}

int	init(t_vars *vars, int argc, char **argv, char **env)
{
	g_signal_received = 0;
	if ((argc == 0) || (argv == NULL))
		return (0);
	vars->env_list = NULL;
	vars->node_list = NULL;
	vars->operators = NULL;
	vars->paths = NULL;
	vars->tokens = NULL;
	vars->here_doc_buf = NULL;
	vars->cmnd_nmbrs = 0;
	vars->return_code = 0;
	vars->im_in_pipe = 0;
	vars->fd_stdin = dup(STDIN_FILENO);
	vars->fd_stdout = dup(STDOUT_FILENO);
	vars->old_fds = ft_calloc(2, sizeof(int));
	vars->old_fds[0] = -1;
	vars->old_fds[1] = -1;
	set_signals(vars);
	create_env_list(&(vars->env_list), env);
	shell_lvl(&(vars->env_list));
	return (0);
}
