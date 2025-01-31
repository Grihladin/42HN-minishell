/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 22:26:03 by mratke            #+#    #+#             */
/*   Updated: 2025/01/31 19:49:41 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_list	*env_listdup(t_env_list *head)
{
	t_env_list	*duplicate;
	t_env_list	*node;
	t_env_list	*current;

	current = head;
	duplicate = NULL;
	while (current)
	{
		node = ft_new_env(current->variable, current->value);
		ft_envadd_back(&duplicate, node);
		current = current->next;
	}
	return (duplicate);
}

static void	swap_content(t_env_list *node1, t_env_list *node2)
{
	char	*tmp_value;
	char	*tmp_var;

	tmp_value = node1->value;
	tmp_var = node1->variable;
	node1->value = node2->value;
	node1->variable = node2->variable;
	node2->value = tmp_value;
	node2->variable = tmp_var;
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
			if (ft_strcmp(current->variable, current->next->variable) > 0)
			{
				swap_content(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
	}
	return (list);
}

static void	print_env_export(t_env_list *sorted_env_list)
{
	t_env_list	*current;

	current = sorted_env_list;
	while (current)
	{
		printf("declare -x %s=%s\n", current->variable, current->value);
		current = current->next;
	}
}

static int	is_valid_var_name(char *str)
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

static void	add_new_env_var(t_env_list **head, char *arg)
{
	char		*value;
	char		*var;
	t_env_list	*node;
	int			i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
		{
			var = ft_substr(arg, 0, i);
			if (!is_valid_var_name(var))
				return ;
			value = ft_strdup(arg + i + 1);
			node = ft_new_env(var, value);
			ft_envadd_back(head, node);
			return ;
		}
		i++;
	}
}

static t_env_list	*is_in_env(t_env_list *head, char *arg)
{
	char		*var;
	int			i;
	t_env_list	*current;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
		{
			var = ft_substr(arg, 0, i - 1);
			break ;
		}
		i++;
	}
	current = head;
	while (current)
	{
		if (!ft_strcmp(current->variable, var))
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	ft_export(t_env_list *env, char **args)
{
	int			i;
	int			j;
	char		*value;
	t_env_list	*node;

	j = 0;
	if (!args)
	{
		print_env_export(sort_env_list(env));
		return ;
	}
	i = 0;
	while (args[i] != NULL)
	{
		node = is_in_env(env, args[i]);
		if (node)
		{
			while (args[i][j] != '\0')
			{
				if (args[i][j] == '=')
				{
					value = ft_strdup(args[i] + j + 1);
					break ;
				}
				j++;
			}
			node->value = value;
		}
		add_new_env_var(&env, args[i]);
		i++;
	}
}
