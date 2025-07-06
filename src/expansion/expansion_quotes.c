/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:37:58 by psenko            #+#    #+#             */
/*   Updated: 2025/02/27 19:09:40 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_next_single_part(char **str)
{
	int		size;
	char	*new_str;

	new_str = NULL;
	size = 0;
	while (((*str)[size] != '$') && ((*str)[size] != '\0')
		&& ((*str)[size] != '"'))
		size++;
	new_str = ft_calloc(size + 1, 1);
	ft_strlcpy(new_str, *str, size + 1);
	*str += size;
	return (new_str);
}

char	*get_next_part_double_quotes(t_vars *vars, char **str)
{
	char	*new_str;
	t_list	*str_list;

	new_str = NULL;
	str_list = NULL;
	(*str)++;
	while (**str != '"')
	{
		if (**str == '$')
			new_str = expansion_get_var(vars, str, 1);
		else
			new_str = get_next_single_part(str);
		add_str_to_list(new_str, &str_list);
	}
	(*str)++;
	new_str = mv_lst_to_str(&str_list);
	return (new_str);
}

char	*get_next_part_single_quotes(char **str)
{
	char	*new_str;
	char	*end;

	new_str = NULL;
	end = ft_strchr(++(*str), '\'');
	new_str = copy_token_to_str(str, end);
	(*str)++;
	return (new_str);
}
