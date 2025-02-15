/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:16:14 by psenko            #+#    #+#             */
/*   Updated: 2025/02/15 17:20:32 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	it_builtin_programm(char *cmnd)
{
	if ((!ft_strcmp("echo", cmnd)) || (!ft_strcmp("cd", cmnd))
		|| (!ft_strcmp("pwd", cmnd)) || (!ft_strcmp("export", cmnd))
		|| (!ft_strcmp("unset", cmnd)) || (!ft_strcmp("exit", cmnd)))
		return (1);
	return (0);
}

static int	execute_builtin_programm(t_vars *vars, char **args)
{
	if (!ft_strcmp("exit", args[0]))
		return (ft_exit(args, vars));
	else if (!ft_strcmp("echo", args[0]))
		return (ft_echo(args));
	else if (!ft_strcmp("cd", args[0]))
		return (ft_cd(vars, args));
	else if (!ft_strcmp("pwd", args[0]))
		return (ft_pwd(vars->env_list));
	else if (!ft_strcmp("export", args[0]))
		return (ft_export(&vars->env_list, args));
	else if (!ft_strcmp("unset", args[0]))
		return (ft_unset(vars, args));
	return (0);
}

static int	execute_programm(t_vars *vars, t_node *node, char **args)
{
	char	*fullpath;
	char	**tmp_env;

	vars->cmnd_nmbrs++;
	get_paths(vars);
	node->command_pid = fork();
	if (node->command_pid == 0)
	{
		fullpath = get_full_path(args[0], vars->paths);
		if (fullpath != NULL)
		{
			tmp_env = env_to_array(vars);
			if (execve(fullpath, args, tmp_env) == -1)
			{
				perror("Execute error!");
				exit(errno);
			}
		}
		else
		{
			tmp_env = env_to_array(vars);
			if (execve(args[0], args, tmp_env) == -1)
			{
				// perror("No file!");
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(args[0], STDERR_FILENO);
				ft_putendl_fd(" command not found", STDERR_FILENO);
				exit(errno);
			}
		}
	}
	free_list(&(vars->paths));
	return (0);
}

int	execute_command(t_vars *vars, t_node *node, char **args)
{
	if (it_builtin_programm(args[0]))
	{
		vars->return_code = execute_builtin_programm(vars, args);
		return (0);
	}
	else
		return (execute_programm(vars, node, args));
	return (0);
}
