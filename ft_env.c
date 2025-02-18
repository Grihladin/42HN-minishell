/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:40:31 by mratke            #+#    #+#             */
/*   Updated: 2025/02/18 21:33:16 by mratke           ###   ########.fr       */
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
	new_node->key = variable;
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

void	create_env_node(t_env_list **head, int j, int i, char **env)
{
	char		*var;
	char		*value;
	t_env_list	*new_node;

	var = ft_substr(env[i], 0, j);
	if (!var)
		return ;
	value = ft_strdup(env[i] + j + 1);
	if (!value)
		return ;
	new_node = ft_new_env(var, value);
	if (!ft_strcmp(new_node->key, "OLDPWD"))
	{
		free(new_node->value);
		new_node->value = ft_strdup("");
	}
	ft_envadd_back(head, new_node);
}

void	create_env_list(t_env_list **head, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0')
		{
			if (env[i][j] == '=')
			{
				create_env_node(head, j, i, env);
				break ;
			}
			j++;
		}
		i++;
	}
}

int	ft_env(t_env_list *head)
{
	if (!head)
		return (1);
	while (head)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return (0);
}
