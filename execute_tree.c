/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:48:58 by mratke            #+#    #+#             */
/*   Updated: 2025/02/07 16:52:07 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_tree(t_node *root)
{
	int	i;

	if (!root)
		return ;
	i = 0;
	if (root->type == COMMAND_TYPE)
	{
		// printf("Command: \n");
		i = 0;
		while (root->command_args && root->command_args[i])
		{
			// command here
			// printf("%s ", root->command_args[i]);
			i++;
		}
		printf("\n");
	}
	// operators here
	else
		printf("Operator: %d\n", root->type);
	execute_tree(root->left);
	execute_tree(root->right);
	// depth need for spaces you can delete it
}
