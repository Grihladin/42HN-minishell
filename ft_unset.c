/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:53:37 by mratke            #+#    #+#             */
/*   Updated: 2025/02/07 16:52:41 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_node(t_env_list **env_list, t_env_list *node,
		t_env_list *prev_node)
{
	t_env_list	*tmp;

	if (prev_node == NULL)
	{
		tmp = *env_list;
		*env_list = (*env_list)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return ;
	}
	prev_node->next = node->next;
	free(node->key);
	free(node->value);
	free(node);
}

static void	env_delone(t_env_list **env_list, t_env_list *node_to_del)
{
	t_env_list	*current;
	t_env_list	*prev_node;

	if (!env_list || !node_to_del)
		return ;
	prev_node = NULL;
	current = *env_list;
	while (current)
	{
		if (current == node_to_del)
		{
			del_node(env_list, node_to_del, prev_node);
			break ;
		}
		prev_node = current;
		current = current->next;
	}
}

void	ft_unset(t_vars *vars, char **args)
{
	t_env_list	*current;
	int			i;

	if (!vars || !args)
		return ;
	i = 1;
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
		{
			i++;
			continue ;
		}
		current = vars->env_list;
		while (current)
		{
			if (!ft_strcmp(current->key, args[i]))
			{
				env_delone(&vars->env_list, current);
				break ;
			}
			current = current->next;
		}
		i++;
	}
}
