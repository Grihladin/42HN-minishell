/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:16:14 by psenko            #+#    #+#             */
/*   Updated: 2025/02/23 11:18:58 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	it_builtin_program(char *cmd)
{
	char	*tmp;

	tmp = ft_strtolower(cmd);
	if ((!ft_strcmp("echo", tmp)) || (!ft_strcmp("cd", tmp))
		|| (!ft_strcmp("pwd", tmp)) || (!ft_strcmp("export", tmp))
		|| (!ft_strcmp("unset", tmp)) || (!ft_strcmp("exit", tmp)))
	{
		ft_strlcpy(cmd, tmp, ft_strlen(cmd) + 1);
		free(tmp);
		return (1);
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
	return (0);
}

static int	execute_program(t_vars *vars, t_node *node, char **args)
{
	char	*fullpath;
	char	**tmp_env;

	vars->cmnd_nmbrs++;
	get_paths(vars);
	node->command_pid = fork();
	if (node->command_pid == 0)
	{
		close_all_fds();
		set_signal_child(vars);
		fullpath = get_full_path(args[0], vars->paths);
		if (fullpath != NULL)
		{
			tmp_env = env_to_array(vars);
			if (execve(fullpath, args, tmp_env) == -1)
			{
				error_message(node, errno);
				exit(errno);
			}
		}
		else
		{
			tmp_env = env_to_array(vars);
			if (execve(args[0], args, tmp_env) == -1)
			{
				error_message(node, ERR_NOT_FOUND);
				exit(ERR_NOT_FOUND);
			}
		}
	}
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
				exit (execute_builtin_program(vars, args));
			else
				vars->last_pid = node->command_pid;
		}
		else
			vars->return_code = execute_builtin_program(vars, args);
		return (0);
	}
	else
		return (execute_program(vars, node, args));
	return (0);
}
