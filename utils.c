/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:53:28 by mratke            #+#    #+#             */
/*   Updated: 2025/02/09 10:48:10 by psenko           ###   ########.fr       */
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

void	print_tree(t_node *node, int depth)
{
	if (!node)
		return ;
	for (int i = 0; i < depth; i++)
		printf("  ");
	if (node->type == COMMAND_TYPE)
	{
		printf("Command: ");
		for (int i = 0; node->command_args[i]; i++)
			printf("%s ", node->command_args[i]);
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

size_t	token_len(char *str)
{
	size_t	cnt;

	cnt = 0;
	if (str != NULL)
	{
		while ((*str != '\0') && (is_operator(str) == 0)
			&& (is_space(str) == 0))
		{
			cnt++;
			str++;
		}
	}
	return (cnt);
}

int	is_operator(char *str)
{
	// {"<<", ">>", "||", "&&", "|", ">", "<"};
	if ((*str == '<') || (*str == '>') || (*str == '|') || (*str == '&'))
	{
		if (*(str + 1) == *str)
			return (2);
		else
			return (1);
	}
	// else if (*str == '$')
	// 	return (3);
	return (0);
}

int	is_space(char *str)
{
	if ((*str != '\0') && ((*str == ' ') || (*str == '\t') || (*str == '\n')
			|| (*str == '\v') || (*str == '\f') || (*str == '\r')))
		return (1);
	return (0);
}
