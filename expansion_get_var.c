/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_get_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:24:10 by psenko            #+#    #+#             */
/*   Updated: 2025/02/27 19:03:24 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (((*str)[size] != '\0') && (ft_isalnum((*str)[size])
			|| ((*str)[size] == '_')))
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

char	*expansion_get_var(t_vars *vars, char **str, char quotes)
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
	else if (((**str != '"') && (**str != '\'') && (is_space(**str) == 0))
		|| quotes)
	{
		new_str = ft_calloc(2, 1);
		ft_strlcpy(new_str, "$", 2);
	}
	return (new_str);
}
