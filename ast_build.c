/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:11:08 by mratke            #+#    #+#             */
/*   Updated: 2025/02/22 16:35:32 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*parse_command(t_list **current)
{
	t_node	*cmd_node;
	char	**args;
	int		arg_count;
	t_list	*temp;
	char	*oper;
	char	*file;
	int		i;

	cmd_node = create_command_node(NULL);
	args = NULL;
	arg_count = 0;
	temp = *current;
	while (temp && type_of_operator(temp->content) != PIPE_TYPE
		&& type_of_operator(temp->content) != AND_TYPE
		&& type_of_operator(temp->content) != OR_TYPE)
	{
		if (type_of_operator(temp->content) == REDIRECT_TYPE)
		{
			oper = temp->content;
			temp = temp->next;
			if (!temp)
				return (NULL);
			file = temp->content;
			create_redirect_node(cmd_node, oper, file);
			temp = temp->next;
		}
		else
		{
			arg_count++;
			temp = temp->next;
		}
	}
	args = malloc((arg_count + 1) * sizeof(char *));
	i = 0;
	temp = *current;
	while (i < arg_count)
	{
		if (type_of_operator(temp->content) == REDIRECT_TYPE)
			temp = temp->next->next;
		else
		{
			args[i] = ft_strdup(temp->content);
			temp = temp->next;
			i++;
		}
	}
	args[arg_count] = NULL;
	cmd_node->command_args = args;
	*current = temp;
	return (cmd_node);
}

static t_node	*parse_redirect(t_list **tokens)
{
	t_node	*left;
	t_list	*current;
	char	*file;
	char	*oper;

	left = parse_command(tokens);
	current = *tokens;
	while (*tokens && type_of_operator(current->content) == REDIRECT_TYPE)
	{
		oper = ft_strdup(current->content);
		*tokens = current->next;
		if (!*tokens)
			return (left);
		current = *tokens;
		file = ft_strdup(current->content);
		left = create_redirect_node(left, oper, file);
		free(oper);
		free(file);
		*tokens = current->next;
		current = *tokens;
	}
	return (left);
}

static t_node	*parse_pipe(t_list **tokens)
{
	t_node	*left;
	t_list	*current;
	t_node	*right;

	left = parse_redirect(tokens);
	current = *tokens;
	while (*tokens && type_of_operator(current->content) == PIPE_TYPE)
	{
		*tokens = current->next;
		right = parse_redirect(tokens);
		left = create_operator_node(PIPE_TYPE, left, right);
		current = *tokens;
	}
	return (left);
}

static t_node	*parse_and_or(t_list **tokens)
{
	t_node	*left;
	t_list	*current;
	t_node	*right;

	left = parse_pipe(tokens);
	current = *tokens;
	while (*tokens && (type_of_operator(current->content) == AND_TYPE
			|| type_of_operator(current->content) == OR_TYPE))
	{
		*tokens = current->next;
		right = parse_tokens(tokens);
		left = create_operator_node(type_of_operator(current->content), left,
				right);
		current = *tokens;
	}
	return (left);
}

t_node	*parse_tokens(t_list **tokens)
{
	return (parse_and_or(tokens));
}
