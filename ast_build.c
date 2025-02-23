/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:11:08 by mratke            #+#    #+#             */
/*   Updated: 2025/02/24 00:09:03 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_control_operator(char *token)
{
	if (ft_strcmp(token, "&&") == 0 || ft_strcmp(token, "||") == 0
		|| ft_strcmp(token, "|") == 0)
		return (1);
	return (0);
}

static t_node	*parse_command(t_list **current)
{
	t_node	*cmd_root;
	t_node	*current_node;
	char	**args;
	t_list	*iter;
	int		arg_count;
	int		i;
	char	*oper;
	char	*file;
	t_node	*redirect;

	cmd_root = create_command_node(NULL);
	current_node = cmd_root;
	iter = *current;
	arg_count = 0;
	while (iter && !is_control_operator(iter->content))
	{
		if (type_of_operator(iter->content) == REDIRECT_TYPE)
		{
			iter = iter->next;
			if (!iter || type_of_operator(iter->content))
				return (NULL);
			iter = iter->next;
		}
		else
		{
			arg_count++;
			iter = iter->next;
		}
	}
	args = malloc((arg_count + 1) * sizeof(char *));
	iter = *current;
	i = 0;
	while (i < arg_count)
	{
		if (type_of_operator(iter->content) == REDIRECT_TYPE)
		{
			oper = iter->content;
			file = iter->next->content;
			redirect = create_redirect_node(current_node, oper, file);
			current_node = redirect;
			iter = iter->next->next;
		}
		else
		{
			args[i++] = ft_strdup(iter->content);
			iter = iter->next;
		}
	}
	args[arg_count] = NULL;
	cmd_root->command_args = args;
	*current = iter;
	return (current_node);
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
