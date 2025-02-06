/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:53:37 by mratke            #+#    #+#             */
/*   Updated: 2025/02/06 18:31:03 by mratke           ###   ########.fr       */
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
		del(tmp->key);
		del(tmp->value);
		free(tmp);
		return ;
	}
	prev_node->next = node->next;
	del(node->key);
	del(node->value);
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

void	ft_unset(t_vars *vars, char *var_to_unset)
{
	t_env_list	*current;

	if (!vars || !var_to_unset || !is_valid_var_name(var_to_unset))
		return ;
	current = vars->env_list;
	while (current)
	{
		if (!ft_strcmp(current->key, var_to_unset))
		{
			env_delone(&vars->env_list, current);
			break ;
		}
		current = current->next;
	}
}
