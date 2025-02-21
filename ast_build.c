/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 20:11:08 by mratke            #+#    #+#             */
/*   Updated: 2025/02/21 15:52:07 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*parse_command(t_list **current, t_vars *vars)
{
	int		arg_count;
	t_list	*temp;
	char	**args;
	int		i;

	i = 0;
	temp = *current;
	if (!temp || type_of_operator(temp->content) == PIPE_TYPE)
		return (printf("syntax error near unexpected token `|'\n"),
			create_command_node(NULL));
	arg_count = calculate_args(temp);
	args = malloc((arg_count + 1) * sizeof(char *));
	while (i < arg_count)
	{
		temp->content = handle_vars(vars, temp->content);
		args[i] = ft_strdup(temp->content);
		if (!args[i])
			return (free_double_array(args), NULL);
		temp = temp->next;
		i++;
	}
	args[arg_count] = NULL;
	return (create_command_node(args));
}

static t_node	*parse_redirect(t_list **tokens, t_vars *vars)
{
	t_node	*left;
	t_list	*current;
	char	*file;
	char	*oper;

	left = parse_command(tokens, vars);
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

static t_node	*parse_pipe(t_list **tokens, t_vars *vars)
{
	t_node	*left;
	t_list	*current;
	t_node	*right;

	left = parse_redirect(tokens, vars);
	current = *tokens;
	while (*tokens && type_of_operator(current->content) == PIPE_TYPE)
	{
		*tokens = current->next;
		right = parse_redirect(tokens, vars);
		left = create_operator_node(PIPE_TYPE, left, right);
		current = *tokens;
	}
	return (left);
}

static t_node	*parse_and_or(t_list **tokens, t_vars *vars)
{
	t_node	*left;
	t_list	*current;
	t_node	*right;

	left = parse_pipe(tokens, vars);
	current = *tokens;
	while (*tokens && (type_of_operator(current->content) == AND_TYPE
			|| type_of_operator(current->content) == OR_TYPE))
	{
		*tokens = current->next;
		right = parse_tokens(tokens, vars);
		left = create_operator_node(type_of_operator(current->content), left,
				right);
		current = *tokens;
	}
	return (left);
}

t_node	*parse_tokens(t_list **tokens, t_vars *vars)
{
	return (parse_and_or(tokens, vars));
}
