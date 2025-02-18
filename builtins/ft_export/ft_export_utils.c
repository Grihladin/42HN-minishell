/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:20:18 by mratke            #+#    #+#             */
/*   Updated: 2025/02/18 22:29:50 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env_list	*env_listdup(t_env_list *head)
{
	t_env_list	*new_list;
	t_env_list	*new_node;
	t_env_list	*current;
	char		*key_copy;
	char		*value_copy;

	new_list = NULL;
	current = head;
	while (current)
	{
		key_copy = ft_strdup(current->key);
		if (!key_copy)
			return (ft_envdel(&new_list, free), NULL);
		value_copy = ft_strdup(current->value);
		if (!value_copy)
			return (free(key_copy), ft_envdel(&new_list, free), NULL);
		new_node = ft_new_env(key_copy, value_copy);
		if (!new_node)
			return (free(key_copy), free(value_copy), ft_envdel(&new_list,
					free), NULL);
		ft_envadd_back(&new_list, new_node);
		current = current->next;
	}
	return (new_list);
}

static void	swap_content(t_env_list *node1, t_env_list *node2)
{
	char	*tmp_value;
	char	*tmp_var;

	tmp_value = node1->value;
	tmp_var = node1->key;
	node1->value = node2->value;
	node1->key = node2->key;
	node2->value = tmp_value;
	node2->key = tmp_var;
}

t_env_list	*sort_env_list(t_env_list *head)
{
	t_env_list	*list;
	t_env_list	*current;
	int			swapped;

	swapped = 1;
	list = env_listdup(head);
	while (swapped)
	{
		swapped = 0;
		current = list;
		while (current && current->next)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
			{
				swap_content(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
	}
	return (list);
}

void	print_env_export(t_env_list *sorted_env_list)
{
	t_env_list	*current;

	current = sorted_env_list;
	while (current)
	{
		if (current->value != NULL && ft_strcmp(current->key, "_"))
		{
			if (!ft_strcmp(current->value, ""))
				printf("declare -x %s\n", current->key);
			else
				printf("declare -x %s=\"%s\"\n", current->key, current->value);
		}
		current = current->next;
	}
}

void	ft_envdel(t_env_list **lst, void (*del)(void *))
{
	t_env_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		del((*lst)->key);
		del((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
}
