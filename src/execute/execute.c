/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:16:14 by psenko            #+#    #+#             */
/*   Updated: 2025/02/27 19:07:26 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	it_builtin_program(char *cmd)
{
	char	*tmp;

	if ((!ft_strcmp("echo", cmd)) || (!ft_strcmp("cd", cmd))
		|| (!ft_strcmp("pwd", cmd)) || (!ft_strcmp("export", cmd))
		|| (!ft_strcmp("unset", cmd)) || (!ft_strcmp("exit", cmd))
		|| (!ft_strcmp("env", cmd)))
		return (1);
	else
	{
		tmp = ft_strtolower(cmd);
		if ((!ft_strcmp("echo", tmp)) || (!ft_strcmp("cd", tmp))
			|| (!ft_strcmp("pwd", tmp)) || (!ft_strcmp("env", tmp)))
		{
			ft_strlcpy(cmd, tmp, ft_strlen(cmd) + 1);
			free(tmp);
			return (1);
		}
		free(tmp);
	}
	return (0);
}

static int	execute_builtin_program(t_vars *vars, char **args)
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
	else if (!ft_strcmp("env", args[0]))
		return (ft_env(vars->env_list));
	return (0);
}

static int	start_fork(t_vars *vars, t_node *node, char **args)
{
	char	*fullpath;
	char	**tmp_env;

	close_all_fds();
	set_signal_child(vars);
	fullpath = get_full_path(args[0], vars->paths);
	if (fullpath != NULL)
	{
		tmp_env = env_to_array(vars->env_list);
		if (execve(fullpath, args, tmp_env) == -1)
		{
			error_message(node, errno);
			exit(errno);
		}
	}
	else
	{
		tmp_env = env_to_array(vars->env_list);
		if (execve(args[0], args, tmp_env) == -1)
		{
			error_message(node, ERR_NOT_FOUND);
			exit(ERR_NOT_FOUND);
		}
	}
	return (0);
}

static int	execute_program(t_vars *vars, t_node *node, char **args)
{
	vars->cmnd_nmbrs++;
	get_paths(vars);
	node->command_pid = fork();
	if (node->command_pid == 0)
		start_fork(vars, node, args);
	else if (node->command_pid < 0)
		return (1);
	set_signal_quit(vars);
	vars->last_pid = node->command_pid;
	free_list(&(vars->paths));
	return (0);
}

int	execute_command(t_vars *vars, t_node *node, char **args)
{
	if (it_builtin_program(args[0]))
	{
		if (vars->im_in_pipe)
		{
			vars->cmnd_nmbrs++;
			node->command_pid = fork();
			if (node->command_pid == 0)
				exit(execute_builtin_program(vars, args));
			else
			{
				vars->last_pid = node->command_pid;
				set_signal_quit(vars);
			}
		}
		else
			vars->return_code = execute_builtin_program(vars, args);
		return (0);
	}
	else
		return (execute_program(vars, node, args));
	return (0);
}
