/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:16:14 by psenko            #+#    #+#             */
/*   Updated: 2025/02/09 19:11:17 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	it_builtin_programm(char *cmnd)
{
	if ((!ft_strcmp("echo", cmnd)) || (!ft_strcmp("cd", cmnd))
		|| (!ft_strcmp("pwd", cmnd)) || (!ft_strcmp("export", cmnd))
		|| (!ft_strcmp("unset", cmnd))|| (!ft_strcmp("exit", cmnd)))
		return (1);
	return (0);
}

static int	execute_builtin_programm(t_vars *vars, char **args)
{
	// builtin programs should execute in fork
	if (!ft_strcmp("echo", args[0]))
		return (ft_echo(args), 1);
	else if (!ft_strcmp("cd", args[0]))
		return (ft_cd(vars, args), 1);
	else if (!ft_strcmp("pwd", args[0]))
		return (ft_pwd(vars->env_list), 1);
	else if (!ft_strcmp("export", args[0]))
		return (ft_export(&vars->env_list, args), 1);
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
			if (execve(fullpath, args, tmp_env) == -1)
			{
				perror("Error!");
				// printf("%s\n", strerror(errno));
				return (1);
			}
		}
		// else
		// 	waitpid(node->command_pid, NULL, 0);
	}
	else
	{
		tmp_env = env_to_array(vars);
		if (execve(args[0], args, tmp_env) == -1)
		{
			perror("Error!");
			// printf("%s\n", strerror(errno));
			return (1);
		}
	}
	return (0);
}

int	execute_command(t_vars *vars, t_node *node, char **args)
{
	if (it_builtin_programm(args[0]))
		return (execute_builtin_programm(vars, args));
	else
		return (execute_programm(vars, node, args));
	return (0);
}
