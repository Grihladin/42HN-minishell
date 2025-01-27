/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:18:13 by mratke            #+#    #+#             */
/*   Updated: 2025/01/27 18:39:09 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_operator_node(t_node_type type, t_node *left, t_node *right)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->command_args = NULL;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

t_node	*create_command_node(char **args)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = COMMAND_TYPE;
	new_node->command_args = args;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_node	*create_redirect_node(t_node *command, char *operator, char *file)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = REDIRECT_TYPE;
	new_node->command_args = ((char *[]){operator, file, NULL});
	new_node->left = command;
	new_node->right = NULL;
	return (new_node);
}
