/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:11:08 by mratke            #+#    #+#             */
/*   Updated: 2025/02/07 20:58:35 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*parse_command(t_list **current)
{
	int		arg_count;
	t_list	*temp;
	char	**args;
	int		i;

	i = 0;
	arg_count = 0;
	temp = *current;
	while (temp && !type_of_operator(temp->content))
	{
		arg_count++;
		temp = temp->next;
	}
	args = malloc((arg_count + 1) * sizeof(char *));
	while (i < arg_count)
	{
		args[i] = ft_strdup((*current)->content);
		if (!args[i])
			return (free_double_array(args), NULL);
		*current = (*current)->next;
		i++;
	}
	args[arg_count] = NULL;
	return (create_command_node(args));
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

// temporary solution because i need an array of strings in command.

t_node	*parse_tokens(t_list **tokens)
{
	return (parse_and_or(tokens));
}
