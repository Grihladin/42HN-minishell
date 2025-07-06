/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:55:51 by mratke            #+#    #+#             */
/*   Updated: 2025/02/26 14:24:19 by mratke           ###   ########.fr       */
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

int	count_command_arguments(t_list *iter)
{
	int	arg_count;

	arg_count = 0;
	while (iter && !is_control_operator(iter->content))
	{
		if (type_of_operator(iter->content) == REDIRECT_TYPE)
		{
			iter = iter->next;
			if (!iter || type_of_operator(iter->content))
				return (arg_count);
			iter = iter->next;
		}
		else
		{
			arg_count++;
			iter = iter->next;
		}
	}
	return (arg_count);
}

t_node	*handle_redirection(t_node *node, t_list **iter)
{
	char	*oper;
	char	*file;
	t_node	*redirect;

	oper = (*iter)->content;
	*iter = (*iter)->next;
	if (!*iter || type_of_operator((*iter)->content))
		return (handle_invalid_redirection(node, oper, iter));
	file = (*iter)->content;
	redirect = create_redirect_node(node, oper, file);
	*iter = (*iter)->next;
	return (redirect);
}

t_node	*handle_invalid_redirection(t_node *node, char *oper, t_list **iter)
{
	t_node	*redirect;

	redirect = create_redirect_node(node, oper, NULL);
	if (*iter)
		*iter = (*iter)->next;
	return (redirect);
}

void	populate_command_arguments(t_node *cmd_root, t_list **current,
		int arg_count)
{
	char	**args;
	int		i;
	t_list	*iter;

	args = malloc((arg_count + 1) * sizeof(char *));
	i = 0;
	iter = *current;
	while (i < arg_count && iter)
	{
		if (type_of_operator(iter->content) == REDIRECT_TYPE)
		{
			iter = iter->next;
			if (iter && !type_of_operator(iter->content))
				iter = iter->next;
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
}
