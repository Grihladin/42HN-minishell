/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:17:26 by psenko            #+#    #+#             */
/*   Updated: 2025/02/27 19:09:37 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_var_n(t_vars *vars, char **str)
{
	int		size;
	char	*new_str;
	char	*tmp_str;
	char	*env_val;

	new_str = NULL;
	tmp_str = NULL;
	env_val = NULL;
	size = 0;
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
	return (new_str);
}

static char	*get_var(t_vars *vars, char **str)
{
	char	*new_str;

	new_str = NULL;
	(*str)++;
	if (**str == '?')
	{
		new_str = ft_itoa(vars->return_code);
		(*str)++;
	}
	else if ((ft_isalnum(**str) || (**str == '_')))
		new_str = get_var_n(vars, str);
	else if (((ft_isalnum(**str) == 0) && ((**str != '_'))))
	{
		new_str = ft_calloc(2, 1);
		ft_strlcpy(new_str, "$", 2);
	}
	return (new_str);
}

static char	*get_next_part(t_vars *vars, char **str)
{
	int		size;
	char	*new_str;

	size = 0;
	new_str = NULL;
	if (**str == '$')
		new_str = get_var(vars, str);
	else
	{
		while (((*str)[size] != '$') && ((*str)[size] != '\0'))
			size++;
		new_str = ft_calloc(size + 1, 1);
		ft_strlcpy(new_str, *str, size + 1);
		*str += size;
		return (new_str);
	}
	return (new_str);
}

char	*handle_vars_heredoc(t_vars *vars, char *str)
{
	char	*new_str;
	char	*old_str;
	t_list	*str_list;
	char	*result_str;

	str_list = NULL;
	new_str = NULL;
	result_str = NULL;
	old_str = str;
	if (ft_strchr(str, '$'))
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
