/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:38:40 by mratke            #+#    #+#             */
/*   Updated: 2025/01/27 22:10:10 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect(char *token)
{
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0
		|| ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
	{
		return (1);
	}
	return (0);
}
// t_node	*parse_tokens(t_list **tokens)
// {
// 	t_node	*left;
// 	t_list	*current;
// 	t_node	*right;
// 	char	*file;

// 	if (!tokens || !*tokens)
// 		return (NULL);
// 	left = NULL;
// 	current = *tokens;
// 	while (current)
// 	{
// 		if (ft_strcmp(current->content, "|") == 0)
// 		{
// 			if (!current->next)
// 				return (left);
// 			*tokens = current->next;
// 			right = parse_tokens(tokens);
// 			left = create_operator_node(PIPE_TYPE, left, right);
// 			break ;
// 		}
// 		else if (is_redirect((char *)current->content))
// 		{
// 			char *operator= ft_strdup(current->content);
// 			if (!current->next)
// 			{
// 				free(operator);
// 				return (left);
// 			}
// 			current = current->next;
// 			file = ft_strdup(current->content);
// 			left = create_redirect_node(left, operator, file);
// 			free(operator);
// 			free(file);
// 			current = current->next;
// 		}
// 		else
// 		{
// 			left = handle_command(&current);
// 			if (!left)
// 				return (NULL);
// 		}
// 	}
// 	*tokens = current;
// 	return (left);
// }

int	main(void)
{
	char	str[100] = "\"echo hi\" | cat << eof";
	t_list	*tokens;

	tokens = tokenize(str);
	print_list(tokens);
}
