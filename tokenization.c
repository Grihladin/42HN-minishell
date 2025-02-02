/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:31:43 by psenko            #+#    #+#             */
/*   Updated: 2025/02/02 14:00:20 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	it_operator(char *str)
// {
// 	;
// }

static char	*copy_token_to_str(char **str, char *end)
{
	size_t	len;
	char	*dst;

	dst = NULL;
	if (end != NULL)
	{
		len = (end - *str) + 1;
		dst = malloc(len + 1 * sizeof(char));
		if (dst == NULL)
			return (NULL);
		ft_strlcpy(dst, *str, len);
	}
	else
	{
		len = ft_strlen(*str);
		dst = ft_strdup(*str);
		if (dst == NULL)
			return (free(dst), NULL);
	}
	*str += len;
	return (dst);
}

// static char	*find_str_end(char **str)
// {
// 	char	*end;

// 	end = NULL;
// 	if (**str == '\'')
// 	{
// 		end = ft_strchr((*str) + 1, '\'');
// 		if (end != NULL)
// 			(*str)++;
// 	}
// 	else if (**str == '"')
// 	{
// 		end = ft_strchr((*str) + 1, '"');
// 		if (end != NULL)
// 			(*str)++;
// 	}
// 	else
// 		end = ft_strchr(*str, ' ');
// 	return (end);
// }

static char	*get_next_token(char **str)
{
	char	*end;
	char	*new_str;

	// {"<<", ">>", "||", "&&", "|", ">", "<"};
	end = NULL;
	new_str = NULL;
	if (is_operator(*str))
	{
		end = *str + is_operator(*str);
		return (copy_token_to_str(str, end));
	}
	else if (**str == '\'')
	{
		end = ft_strchr((*str) + 1, '\'');
		if (end != NULL)
			(*str)++;
		return (copy_token_to_str(str, end));
	}
	else if (**str == '"')
	{
		end = ft_strchr((*str) + 1, '"');
		if (end != NULL)
			(*str)++;
		// Handle $ for variables
		new_str = copy_token_to_str(str, end);
		return (new_str);
	}
	else
	{
		end = ft_strchr(*str, ' ');
		return (copy_token_to_str(str, end));
	}
	return (end);
}

t_list	*tokenize(t_vars *vars, char *str)
{
	// char	*end;
	char	*new_str;
	t_list	*str_list;
	t_list	*tmp;

	str_list = NULL;
	new_str = NULL;
	if (vars->tokens != NULL)
		free_list(&(vars->tokens));
	while (*str != '\0')
	{
		while ((*str != '\0') && ((*str == ' ') || (*str == '\t')
				|| (*str == '\n') || (*str == '\v')
				|| (*str == '\f') || (*str == '\r')))
			str++;
		// end = find_str_end(&str);
		// new_str = copy_token_to_str(&str, end);
		new_str = get_next_token(&str);
		if (new_str == NULL)
			return (ft_lstclear(&str_list, free), NULL);
		tmp = ft_lstnew(new_str);
		if (tmp == NULL)
			return (ft_lstclear(&tmp, free), NULL);
		ft_lstadd_back(&str_list, tmp);
	}
	print_list(str_list);
	return (str_list);
}
