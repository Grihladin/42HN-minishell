/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:11:08 by mratke            #+#    #+#             */
/*   Updated: 2025/02/27 17:17:47 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_node	*parse_command(t_list *current)
{
	t_node	*cmd_root;
	t_node	*current_node;
	t_list	*iter;
	int		arg_count;

	cmd_root = create_command_node(NULL);
	current_node = cmd_root;
	iter = current;
	arg_count = count_command_arguments(iter);
	iter = current;
	while (iter && !is_control_operator(iter->content))
	{
		if (type_of_operator(iter->content) == REDIRECT_TYPE)
		{
			current_node = handle_redirection(current_node, &iter);
			if (!iter || type_of_operator(iter->content))
				break ;
		}
		else
			iter = iter->next;
	}
	populate_command_arguments(cmd_root, current, arg_count);
	current = iter;
	return (current_node);
}

static t_node	*parse_redirect(t_list *tokens)
{
	t_node	*left;
	t_list	*current;
	char	*file;
	char	*oper;

	left = parse_command(tokens);
	current = tokens;
	while (tokens && type_of_operator(current->content) == REDIRECT_TYPE)
	{
		oper = ft_strdup(current->content);
		tokens = current->next;
		if (!tokens)
			return (left);
		current = tokens;
		file = ft_strdup(current->content);
		left = create_redirect_node(left, oper, file);
		free(oper);
		free(file);
		tokens = current->next;
		current = tokens;
	}
	return (left);
}

static t_node	*parse_pipe(t_list *tokens)
{
	t_node	*left;
	t_list	*current;
	t_node	*right;

	left = parse_redirect(tokens);
	current = tokens;
	while (tokens && type_of_operator(current->content) == PIPE_TYPE)
	{
		tokens = current->next;
		right = parse_redirect(tokens);
		left = create_operator_node(PIPE_TYPE, left, right);
		current = tokens;
	}
	return (left);
}

static t_node	*parse_and_or(t_list *tokens)
{
	t_node	*left;
	t_list	*current;
	t_node	*right;

	left = parse_pipe(tokens);
	current = tokens;
	while (tokens && (type_of_operator(current->content) == AND_TYPE
			|| type_of_operator(current->content) == OR_TYPE))
	{
		tokens = current->next;
		right = parse_tokens(tokens);
		left = create_operator_node(type_of_operator(current->content), left,
				right);
		current = tokens;
	}
	return (left);
}

t_node	*parse_tokens(t_list *tokens)
{
	return (parse_and_or(tokens));
}
