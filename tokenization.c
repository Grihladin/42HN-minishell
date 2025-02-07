/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:31:43 by psenko            #+#    #+#             */
/*   Updated: 2025/02/07 21:41:25 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ls|cat Makefile|cat<<'asd'>out in this case need to save '' as part of the token
// crucial moment fore $ expand

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
		*str = end;
	}
	else
	{
		len = ft_strlen(*str);
		dst = ft_strdup(*str);
		if (dst == NULL)
			return (free(dst), NULL);
		*str += len;
	}
	return (dst);
}

static char	*get_next_token(t_vars *vars, char **str)
{
	char	*end;
	char	*new_str;
	char	*tmp_str;

	end = NULL;
	new_str = NULL;
	tmp_str = NULL;
	if (is_operator(*str))
	{
		end = *str + is_operator(*str);
		return (copy_token_to_str(str, end));
	}
	else if (**str == '"')
	{
		end = ft_strchr(++(*str), '"');
		new_str = copy_token_to_str(str, end);
		(*str)++;
		if (ft_strchr(new_str, '$'))
		{
			tmp_str = handle_env_var(vars, new_str);
			free(new_str);
			new_str = tmp_str;
		}
		return (new_str);
	}
	else if (**str == '\'')
	{
		end = ft_strchr(++(*str), '\'');
		new_str = copy_token_to_str(str, end);
		(*str)++;
		return (new_str);
	}
	else
	{
		end = *str + token_len(*str);
		new_str = copy_token_to_str(str, end);
		if (ft_strchr(new_str, '$'))
		{
			tmp_str = handle_env_var(vars, new_str);
			free(new_str);
			new_str = tmp_str;
		}
		return (new_str);
	}
	return (new_str);
}

t_list	*tokenize(t_vars *vars, char *str)
{
	char	*new_str;
	t_list	*str_list;
	t_list	*tmp;

	str_list = NULL;
	new_str = NULL;
	if (vars->tokens != NULL)
		free_list(&(vars->tokens));
	while (*str != '\0')
	{
		while (is_space(str))
			str++;
		new_str = get_next_token(vars, &str);
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
