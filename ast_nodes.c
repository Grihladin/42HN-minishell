/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:18:13 by mratke            #+#    #+#             */
/*   Updated: 2025/02/07 21:44:50 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Set the node type (PIPE_TYPE, AND_TYPE)
// Operator nodes don't have command arguments
// Set the left child
// Set the right child

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
	new_node->env = NULL;
	new_node->command_pid = 0;
	return (new_node);
}

// Set the command arguments (["echo", "hi", NULL])
// Command nodes don't have left children
// Command nodes don't have right children
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
	///////HANDLE pid and env
	return (new_node);
}

// Set the redirection operator ("<<")
// Set the file or delimiter ("eof")
// Null-terminate the array
// Set the node type to REDIRECT_TYPE
// Set the redirection arguments
// Set the command being redirected
// Redirection nodes don't have right children
t_node	*create_redirect_node(t_node *command, char *operator, char * file)
{
	t_node	*new_node;
	char	**args;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	args = malloc(3 * sizeof(char *));
	if (!args)
		return (free(new_node), NULL);
	args[0] = ft_strdup(operator);
	args[1] = ft_strdup(file);
	args[2] = NULL;
	if (!args[0] || !args[1])
		return (free_double_array(args), NULL);
	new_node->type = REDIRECT_TYPE;
	if (!new_node)
		return (NULL);
	new_node->command_args = args;
	new_node->left = command;
	new_node->right = NULL;
	new_node->env = NULL;
	new_node->command_pid = 0;
	return (new_node);
}

int	type_of_operator(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<")
		|| !ft_strcmp(str, "<<"))
		return (REDIRECT_TYPE);
	else if (!ft_strcmp(str, "|"))
		return (PIPE_TYPE);
	else if (!ft_strcmp(str, "&&"))
		return (AND_TYPE);
	else if (!ft_strcmp(str, "||"))
		return (OR_TYPE);
	return (COMMAND_TYPE);
}

void	clear_tree(t_node *root)
{
	if (!root)
		return ;
	if (root->type == COMMAND_TYPE)
	{
		free_double_array(root->command_args);
		free(root);
		return ;
	}
	clear_tree(root->left);
	clear_tree(root->right);
	free_double_array(root->command_args);
	free(root);
}
