/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:55:31 by mratke            #+#    #+#             */
/*   Updated: 2025/02/05 22:41:25 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_vars *vars, char *dir)
{
	t_env_list	*node;

	if (!vars || !dir)
		return ;
	node = vars->env_list;
	while (node)
	{
		if (!ft_strcmp(node->key, "PWD"))
		{
			free(node->value);
			node->value = dir;
			break ;
		}
		node = node->next;
	}
}

static void	update_old_pwd(t_vars *vars, char *dir)
{
	t_env_list	*node;

	if (!vars || !dir)
		return ;
	node = vars->env_list;
	while (node)
	{
		if (!ft_strcmp(node->key, "OLDPWD"))
		{
			free(node->value);
			node->value = dir;
			break ;
		}
		node = node->next;
	}
}

static int	handle_minus(char **new_dir, char *old_pwd)
{
	*new_dir = getenv("OLDPWD");
	if (!new_dir)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
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
	free(tmp);
	if (dir[0] == '~')
		free(new_dir);
}

void	ft_cd(t_vars *vars, char *dir)
{
	char	*old_pwd;
	char	*new_dir;

	old_pwd = getcwd(NULL, 0);
	if (!dir || !*dir)
		new_dir = getenv("HOME");
	else if (!ft_strcmp(dir, "-"))
	{
		if (handle_minus(&new_dir, old_pwd))
			return ;
	}
	else if (dir[0] == '~')
		new_dir = ft_strjoin(getenv("HOME"), dir + 1);
	else
		new_dir = dir;
	if (chdir(new_dir) == -1)
	{
		perror("cd");
		free(old_pwd);
		if (dir[0] == '~')
			free(new_dir);
		return ;
	}
	update_env(vars, old_pwd, dir, new_dir);
}
