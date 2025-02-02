/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:53:28 by mratke            #+#    #+#             */
/*   Updated: 2025/02/02 14:00:21 by psenko           ###   ########.fr       */
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
		printf("Node %i, content: %s\n", i, head->content);
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
	else if (*str == '$')
		return (3);
	return (0);
}
