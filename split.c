/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:31:43 by psenko            #+#    #+#             */
/*   Updated: 2025/01/26 17:41:19 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*split_copy_str(char **str, char *end)
{
	size_t	len;
	char	*dst;

	dst = NULL;
	if (end != NULL)
	{
		len = (end - *str) + 1;
		dst = ft_calloc(len + 1, sizeof(char));
		if (dst == NULL)
			return (NULL);
		ft_strlcpy(dst, *str, len);
	}
	else
	{
		len = ft_strlen(*str);
		dst = ft_strdup(*str);
		if (dst == NULL)
			return (delete_content(dst), NULL);
	}
	*str += len;
	return (dst);
}

static char	*find_str_end(char **str)
{
	char	*end;

	end = NULL;
	if (**str == '\'')
	{
		end = ft_strchr((*str) + 1, '\'');
		if (end != NULL)
			(*str)++;
	}
	else if (**str == '"')
	{
		end = ft_strchr((*str) + 1, '"');
		if (end != NULL)
			(*str)++;
	}
	else
		end = ft_strchr(*str, ' ');
	return (end);
}

t_list	*split(char *str)
{
	char	*end;
	char	*new_str;
	t_list	*str_list;
	t_list	*tmplst;

	str_list = NULL;
	new_str = NULL;
	while (*str != '\0')
	{
		// Skip spaces - change to function
		while (*str == ' ')
			str++;
		end = find_str_end(&str);
		new_str = split_copy_str(&str, end);
		if (new_str == NULL)
			return (free_list(&str_list), NULL);
		tmplst = ft_lstnew(new_str);
		if (tmplst == NULL)
			return (delete_content(new_str), free_list(&str_list), NULL);
		ft_lstadd_back(&str_list, tmplst);
	}
	return (str_list);
}
