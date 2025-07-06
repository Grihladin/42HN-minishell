/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 22:26:03 by mratke            #+#    #+#             */
/*   Updated: 2025/02/26 14:06:26 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_list	*separate_line(char *str, int i)
{
	t_env_list	*node;
	char		*key;
	char		*value;

	key = ft_substr(str, 0, i);
	if (!key || !is_valid_var_name(key))
		return (free(key), NULL);
	if (str[i] == '=')
		value = ft_strdup(str + i + 1);
	else
		value = NULL;
	if (value == NULL && str[i] == '=')
		return (free(key), NULL);
	node = ft_new_env(key, value);
	if (!node)
	{
		free(key);
		free(value);
		return (NULL);
	}
	return (node);
}

t_env_list	*env_split_line(char *str)
{
	int			i;
	t_env_list	*node;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			node = separate_line(str, i);
			if (!node)
				return (NULL);
			return (node);
		}
		i++;
	}
	node = separate_line(str, i);
	if (!node)
		return (NULL);
	return (node);
}

static int	add_new_env_line(t_env_list **head, char *arg)
{
	t_env_list	*node;

	node = env_split_line(arg);
	if (!node)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	ft_envadd_back(head, node);
	return (0);
}

static void	replace_value(t_env_list *node, char **args, int i)
{
	t_env_list	*tmp;

	tmp = env_split_line(args[i]);
	free(node->value);
	node->value = tmp->value;
	free(tmp->key);
	free(tmp);
}

int	ft_export(t_env_list **env, char **args)
{
	t_env_list	*node;
	t_env_list	*sorted_list;
	int			i;

	if (!args || !args[1])
	{
		sorted_list = sort_env_list(*env);
		if (!sorted_list)
			return (1);
		print_env_export(sorted_list);
		ft_envdel(&sorted_list, free);
		return (0);
	}
	i = 1;
	while (args[i] != NULL)
	{
		node = is_in_env(*env, args[i]);
		if (node)
			replace_value(node, args, i);
		else if (add_new_env_line(env, args[i]))
			return (1);
		i++;
	}
	return (0);
}
