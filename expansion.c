/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:17:26 by psenko            #+#    #+#             */
/*   Updated: 2025/02/26 18:21:51 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var(t_vars *vars, char **str, char quotes)
{
	int		size;
	char	*new_str;
	char	*tmp_str;
	char	*env_val;

	new_str = NULL;
	tmp_str = NULL;
	env_val = NULL;
	size = 0;
	(*str)++;
	if (**str == '?')
	{
		new_str = ft_itoa(vars->return_code);
		(*str)++;
	}
	else if ((ft_isalnum(**str) || (**str == '_')))
	{
		while (((*str)[size] != '\0')
			&& (ft_isalnum((*str)[size]) || ((*str)[size] == '_')))
			size++;
		tmp_str = ft_calloc(size + 1, 1);
		ft_strlcpy(tmp_str, *str, size + 1);
		*str += size;
		env_val = find_var_env(vars->env_list, tmp_str);
		if (env_val != NULL)
			new_str = ft_strdup(env_val);
		free(tmp_str);
	}
	else if (((**str != '"') && (**str != '\'') && (is_space(**str) == 0))
		|| quotes)
	{
		new_str = ft_calloc(2, 1);
		ft_strlcpy(new_str, "$", 2);
	}
	return (new_str);
}

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

static char	*get_next_part(t_vars *vars, char **str)
{
	int		size;
	char	*new_str;
	t_list	*str_list;
	char	*end;

	size = 0;
	new_str = NULL;
	str_list = NULL;
	if (**str == '"')
	{
		(*str)++;
		while (**str != '"')
		{
			if (**str == '$')
				new_str = get_var(vars, str, 1);
			else
				new_str = get_next_single_part(str);
			add_str_to_list(new_str, &str_list);
		}
		(*str)++;
		new_str = mv_lst_to_str(&str_list);
	}
	else if (**str == '\'')
	{
		end = ft_strchr(++(*str), '\'');
		new_str = copy_token_to_str(str, end);
		(*str)++;
	}
	else if (**str == '$')
		new_str = get_var(vars, str, 0);
	else if (ft_strcmp(*str, "~") == 0)
	{
		new_str = get_home(vars);
		(*str)++;
	}
	else
	{
		while (((*str)[size] != '$') && ((*str)[size] != '\'')
				&& ((*str)[size] != '"') && ((*str)[size] != '\0'))
			size++;
		new_str = ft_calloc(size + 1, 1);
		ft_strlcpy(new_str, *str, size + 1);
		*str += size;
		return (new_str);
	}
	return (new_str);
}

char	*handle_vars(t_vars *vars, char *str)
{
	char	*new_str;
	char	*old_str;
	t_list	*str_list;
	t_list	*tmplst;
	char	*result_str;

	str_list = NULL;
	new_str = NULL;
	tmplst = NULL;
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
	int		i;
	char	**tmp;

	tmp = arr;
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
