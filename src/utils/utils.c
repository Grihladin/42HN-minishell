/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:53:28 by mratke            #+#    #+#             */
/*   Updated: 2025/02/27 17:50:41 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_array(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	print_list(t_list *head)
{
	int	i;

	i = 1;
	while (head != NULL)
	{
		printf("Node %i, content: %s\n", i, (char *)head->content);
		i++;
		head = head->next;
	}
}

char	*token_end(char *str)
{
	char	*end;

	end = NULL;
	if (str != NULL)
	{
		if (*str == '"')
			end = ft_strchr(++(str), '"');
		else if (*str == '\'')
			end = ft_strchr(++(str), '\'');
		else
		{
			while ((*str != '\0') && (is_operator(str) == 0)
				&& (is_space(*str) == 0) && (*str != '\'') && (*str != '"'))
				str++;
			end = str;
		}
	}
	return (end);
}

int	is_operator(char *str)
{
	if ((*str == '<') || (*str == '>') || (*str == '|') || (*str == '&'))
	{
		if (*(str + 1) == *str)
			return (2);
		else
			return (1);
	}
	return (0);
}
