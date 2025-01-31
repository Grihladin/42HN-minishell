/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:40:31 by mratke            #+#    #+#             */
/*   Updated: 2025/01/31 17:52:44 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*ft_new_env(char *variable, char *value)
{
	t_env_list	*new_node;

	new_node = malloc(sizeof(t_env_list));
	if (new_node == NULL)
	{
		return (NULL);
	}
	new_node->next = NULL;
	new_node->variable = variable;
	new_node->value = value;
	return (new_node);
}
void	ft_envadd_back(t_env_list **head, t_env_list *new_node)
{
	t_env_list	*current;

	if (new_node == NULL)
	{
		return ;
	}
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_node;
	return ;
}

void	create_env_list(t_env_list **head, char **env) 
{
	int			i;
	int			j;
	char		*value;
	char		*var;
	t_env_list	*new_node;

	value = NULL;
	var = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0')
		{
			if (env[i][j] == '=')
			{
				var = malloc((j + 1) * sizeof(char));
				ft_strlcpy(var, env[i], j + 1);
				value = ft_strdup(env[i] + j + 1);
				new_node = ft_new_env(var, value);
				ft_envadd_back(head, new_node);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	print_env_list(t_env_list *head)
{
	int	i;

	i = 1;
	while (head)
	{
		printf("var: %s, value: %s\n", head->variable, head->value);
		i++;
		head = head->next;
	}
}
