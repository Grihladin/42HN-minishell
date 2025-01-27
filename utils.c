/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:53:28 by mratke            #+#    #+#             */
/*   Updated: 2025/01/27 18:22:09 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
