/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:05:02 by mratke            #+#    #+#             */
/*   Updated: 2025/02/18 21:06:24 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_vars *vars, char *dir)
{
	t_env_list	*node;
	t_env_list	*new_node;

	if (!vars || !dir)
		return ;
	node = vars->env_list;
	while (node)
	{
		if (!ft_strcmp(node->key, "PWD"))
		{
			free(node->value);
			node->value = dir;
			return ;
		}
		node = node->next;
	}
	new_node = ft_new_env(ft_strdup("PWD"), dir);
	if (!new_node)
	{
		free(dir);
		return ;
	}
	ft_envadd_back(&vars->env_list, new_node);
}

void	update_old_pwd(t_vars *vars, char *dir)
{
	t_env_list	*node;
	t_env_list	*new_node;

	if (!vars || !dir)
		return ;
	node = vars->env_list;
	while (node)
	{
		if (!ft_strcmp(node->key, "OLDPWD"))
		{
			free(node->value);
			node->value = dir;
			return ;
		}
		node = node->next;
	}
	new_node = ft_new_env(ft_strdup("OLDPWD"), dir);
	if (!new_node)
	{
		free(dir);
		return ;
	}
	ft_envadd_back(&vars->env_list, new_node);
}
