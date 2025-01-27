/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:38:40 by mratke            #+#    #+#             */
/*   Updated: 2025/01/27 21:43:38 by mratke           ###   ########.fr       */
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

int	main(void)
{
	char	str[100] = "\"echo hi\" | cat << eof";
	t_list	*tokens;

	tokens = tokenize(str);
	print_list(tokens);
}
