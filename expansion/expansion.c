/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:17:26 by psenko            #+#    #+#             */
/*   Updated: 2025/02/27 19:09:46 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_next_singl_part(char **str)
{
	int		size;
	char	*new_str;

	size = 0;
	new_str = NULL;
	while (((*str)[size] != '$') && ((*str)[size] != '\'')
			&& ((*str)[size] != '"') && ((*str)[size] != '\0'))
		size++;
	new_str = ft_calloc(size + 1, 1);
	ft_strlcpy(new_str, *str, size + 1);
	*str += size;
	return (new_str);
}

static char	*get_next_part(t_vars *vars, char **str)
{
	char	*new_str;

	new_str = NULL;
	if (**str == '"')
		new_str = get_next_part_double_quotes(vars, str);
	else if (**str == '\'')
		new_str = get_next_part_single_quotes(str);
	else if (**str == '$')
		new_str = expansion_get_var(vars, str, 0);
	else if (ft_strcmp(*str, "~") == 0)
	{
		new_str = get_home(vars);
		(*str)++;
	}
	else
		new_str = get_next_singl_part(str);
	return (new_str);
}

char	*handle_vars(t_vars *vars, char *str)
{
	char	*new_str;
	char	*old_str;
	t_list	*str_list;
	char	*result_str;

	str_list = NULL;
	new_str = NULL;
	result_str = NULL;
	old_str = str;
	if (ft_strchr(str, '\'') || ft_strchr(str, '"') || ft_strchr(str, '$')
		|| ft_strchr(str, '~'))
	{
		while (*str != '\0')
		{
			new_str = get_next_part(vars, &str);
			add_str_to_list(new_str, &str_list);
		}
		result_str = mv_lst_to_str(&str_list);
		free(old_str);
		str = result_str;
	}
	return (str);
}

int	expansion(t_vars *vars, char **arr)
{
	int	i;

	while (*arr != NULL)
	{
		*arr = handle_vars(vars, *arr);
		arr++;
	}
	while ((*arr != NULL) && (ft_strlen(*arr) == 0))
	{
		i = 0;
		while (arr[i + 1] != NULL)
		{
			arr[i] = arr[i + 1];
			i++;
		}
		arr[i] = arr[i + 1];
	}
	return (0);
}
