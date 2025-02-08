/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:16:14 by psenko            #+#    #+#             */
/*   Updated: 2025/02/08 12:35:06 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_builtin_programm(t_vars *vars, char **args)
{
	if (!ft_strcmp("echo", args[0]))
		return (ft_echo(args), 1);
	else if (!ft_strcmp("cd", args[0]))
		return (ft_cd(vars, args), 1);
	else if (!ft_strcmp("pwd", args[0]))
		return (ft_pwd(vars->env_list), 1);
	else if (!ft_strcmp("export", args[0]))
		return (ft_export(vars->env_list, args), 1);
	else if (!ft_strcmp("unset", args[0]))
		return (ft_unset(vars, args), 1);
	else if (!ft_strcmp("exit", args[0]))
		return (ft_exit(args), 1);
	return (0);
}

static int	execute_programm(t_vars *vars, t_node *node, char **args)
{
	char	*fullpath;
	char	**tmp_env;

	fullpath = get_full_path(args[0], vars->paths);
	if (fullpath != NULL)
	{
		node->command_pid = fork();
		if (node->command_pid == 0)
		{
			tmp_env = env_to_array(vars);
			execve(fullpath, args, tmp_env);
		}
		else
			wait(0);
	}
	return (0);
}

// static int	execute_programm(t_vars *vars, char *cmnd, char **args, char **env)
int	execute_command(t_vars *vars, t_node *node, char **args)
{
	if (execute_builtin_programm(vars, args))
		return (0);
	else
	{
		execute_programm(vars, node, args);
	}
	return (0);
}
