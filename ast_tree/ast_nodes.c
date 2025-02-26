/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:18:13 by mratke            #+#    #+#             */
/*   Updated: 2025/02/26 14:25:58 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_node	*create_new_node(void)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->new_fds = ft_calloc(2, sizeof(int));
	new_node->old_fds = ft_calloc(2, sizeof(int));
	if (new_node->new_fds == NULL || new_node->old_fds == NULL)
		return (free(new_node), NULL);
	new_node->new_fds[0] = -1;
	new_node->new_fds[1] = -1;
	new_node->old_fds[0] = -1;
	new_node->old_fds[1] = -1;
	new_node->command_pid = 0;
	return (new_node);
}

// Set the node type (PIPE_TYPE, AND_TYPE)
// Operator nodes don't have command arguments
// Set the left child
// Set the right child

t_node	*create_operator_node(t_node_type type, t_node *left, t_node *right)
{
	t_node	*new_node;

	new_node = create_new_node();
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

// Set the command arguments (["echo", "hi", NULL])
// Command nodes don't have left children
// Command nodes don't have right children

t_node	*create_command_node(char **args)
{
	t_node	*new_node;

	new_node = create_new_node();
	if (!new_node)
		return (NULL);
	new_node->type = COMMAND_TYPE;
	new_node->command_args = args;
	return (new_node);
}

// Set the redirection operator ("<<")
// Set the file or delimiter ("eof")
// Null-terminate the array
// Set the node type to REDIRECT_TYPE
// Set the redirection arguments
// Set the command being redirected
// Redirection nodes don't have right children

static char	**create_redirect_args(char *operator, char *file)
{
	char	**args;

	args = malloc(3 * sizeof(char *));
	if (!args)
		return (NULL);
	args[0] = NULL;
	args[1] = NULL;
	args[2] = NULL;
	if (operator)
	{
		args[0] = ft_strdup(operator);
		if (!args[0])
			return (free_double_array(args), NULL);
	}
	if (file)
	{
		args[1] = ft_strdup(file);
		if (!args[1])
			return (free_double_array(args), NULL);
	}
	return (args);
}

t_node	*create_redirect_node(t_node *command, char *operator, char *file)
{
	t_node	*new_node;
	char	**args;

	new_node = create_new_node();
	if (!new_node)
		return (NULL);
	args = create_redirect_args(operator, file);
	if (!args)
	{
		free(new_node);
		return (NULL);
	}
	new_node->type = REDIRECT_TYPE;
	new_node->command_args = args;
	new_node->left = command;
	return (new_node);
}
