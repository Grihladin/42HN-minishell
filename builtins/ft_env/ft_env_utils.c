/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:31:59 by mratke            #+#    #+#             */
/*   Updated: 2025/02/18 22:45:53 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_var_env(t_env_list *head, char *var)
{
	while (head != NULL)
	{
		if (ft_strcmp(var, head->key) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

int	env_lstsize(t_env_list *lst)
{
	int			i;
	t_env_list	*current;

	i = 0;
	current = lst;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}
