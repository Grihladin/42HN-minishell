/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:50:59 by mratke            #+#    #+#             */
/*   Updated: 2025/02/18 22:29:54 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valid_var_name(char *str)
{
	if (!str || !*str || ft_isdigit(*str))
		return (0);
	if (!ft_strcmp(str, "_"))
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

t_env_list	*is_in_env(t_env_list *head, char *arg)
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
