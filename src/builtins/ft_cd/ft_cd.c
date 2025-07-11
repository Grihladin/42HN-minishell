/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:55:31 by mratke            #+#    #+#             */
/*   Updated: 2025/02/18 22:29:21 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_minus(t_env_list *env_list, char **new_dir, char *old_pwd)
{
	*new_dir = find_var_env(env_list, "OLDPWD");
	if (!*new_dir || !ft_strcmp(*new_dir, ""))
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		if (old_pwd)
			free(old_pwd);
		return (1);
	}
	ft_putstr_fd(*new_dir, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}

static void	update_env(t_vars *vars, char *old_pwd, char *dir, char *new_dir)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	update_old_pwd(vars, old_pwd);
	update_pwd(vars, tmp);
	if (dir && dir[0] == '~')
		free(new_dir);
}

static char	*handle_tilde_path(t_vars *vars, const char *arg)
{
	char	*home;

	home = find_var_env(vars->env_list, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (NULL);
	}
	return (ft_strjoin(home, arg + 1));
}

static int	change_directory(char *new_dir, char **args)
{
	if (chdir(new_dir) == -1)
	{
		perror("cd");
		if (args[1] && args[1][0] == '~')
			free(new_dir);
		return (1);
	}
	return (0);
}

int	ft_cd(t_vars *vars, char **args)
{
	char	*old_pwd;
	char	*new_dir;

	if (!vars || !args)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	if (!args[1])
		new_dir = find_var_env(vars->env_list, "HOME");
	else if (!ft_strcmp(args[1], "-"))
	{
		if (handle_minus(vars->env_list, &new_dir, old_pwd))
			return (1);
	}
	else if (args[1][0] == '~')
		new_dir = handle_tilde_path(vars, args[1]);
	else
		new_dir = args[1];
	if (!new_dir || change_directory(new_dir, args))
		return (free(old_pwd), 1);
	update_env(vars, old_pwd, args[1], new_dir);
	return (0);
}
