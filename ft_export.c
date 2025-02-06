/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 22:26:03 by mratke            #+#    #+#             */
/*   Updated: 2025/02/06 18:27:31 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_name(char *str)
{
	if (!str || !*str || ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

// split env in node t_env_list
static t_env_list	*env_split_line(char *str)
{
	char		*key;
	char		*value;
	int			i;
	t_env_list	*node;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			key = ft_substr(str, 0, i);
			if (!key || !is_valid_var_name(key))
				return (free(key), NULL);
			value = ft_strdup(str + i + 1);
			if (!value)
				return (free(key), NULL);
			node = ft_new_env(key, value);
			if (!node)
				return (free(key), free(value), NULL);
			return (node);
		}
		i++;
	}
	return (NULL);
}

static void	add_new_env_line(t_env_list **head, char *arg)
{
	t_env_list	*node;

	node = env_split_line(arg);
	if (!node)
		return ;
	ft_envadd_back(head, node);
}

static t_env_list	*is_in_env(t_env_list *head, char *arg)
{
	char		*var;
	t_env_list	*tmp;
	t_env_list	*current;

	tmp = env_split_line(arg);
	if (!tmp)
		return (NULL);
	var = tmp->key;
	current = head;
	while (current)
	{
		if (!ft_strcmp(current->key, var))
		{
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (current);
		}
		current = current->next;
	}
	return (free(tmp->key), free(tmp->value), free(tmp), NULL);
}

void	ft_export(t_env_list *env, char **args)
{
	t_env_list	*tmp;
	t_env_list	*node;
	t_env_list	*sorted_list;
	int			i;

	if (!args)
	{
		sorted_list = sort_env_list(env);
		print_env_export(sorted_list);
		ft_envdel(&sorted_list, free);
		return ;
	}
	i = 0;
	while (args[i] != NULL)
	{
		node = is_in_env(env, args[i]);
		if (node)
		{
			tmp = env_split_line(args[i]);
			free(node->value);
			node->value = tmp->value;
			free(tmp->key);
			free(tmp);
		}
		else
			add_new_env_line(&env, args[i]);
		i++;
	}
}
