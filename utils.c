/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:53:28 by mratke            #+#    #+#             */
/*   Updated: 2025/02/03 21:42:46 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_array(char **arr)
{
	int	i;

	if (!arr)
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

void	print_tree(t_node *root, int depth)
{
	int	i;

	if (!root)
		return ;
	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
	if (root->type == COMMAND_TYPE)
	{
		printf("Command: ");
		i = 0;
		while (root->command_args && root->command_args[i])
		{
			printf("%s ", root->command_args[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf("Operator: %d\n", root->type);
	print_tree(root->left, depth + 1);
	print_tree(root->right, depth + 1);
}

size_t	token_len(char *str)
{
	size_t		cnt;

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
	if ((*str != '\0') && ((*str == ' ') || (*str == '\t')
			|| (*str == '\n') || (*str == '\v')
			|| (*str == '\f') || (*str == '\r')))
		return (1);
	return (0);
}
