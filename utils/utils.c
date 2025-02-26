/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:53:28 by mratke            #+#    #+#             */
/*   Updated: 2025/02/26 14:13:02 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	print_tree(t_node *node, int depth)
{
	if (!node)
		return ;
	for (int i = 0; i < depth; i++)
		printf("  ");
	if (node->type == COMMAND_TYPE)
	{
		printf("Command: ");
		if (node->command_args)
		{
			for (int i = 0; node->command_args[i]; i++)
			printf("%s ", node->command_args[i]);
		}
		printf("\n");
	}
	else if (node->type == REDIRECT_TYPE)
	{
		printf("Operator: REDIRECT\n");
		for (int i = 0; node->command_args[i]; i++)
			printf("%s ", node->command_args[i]);
		printf("\n");
		print_tree(node->left, depth + 1);
	}
	else
	{
		printf("Operator: %s\n",
			node->type == PIPE_TYPE ? "PIPE" : node->type == AND_TYPE ? "AND" : "OR");
		print_tree(node->left, depth + 1);
		print_tree(node->right, depth + 1);
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
