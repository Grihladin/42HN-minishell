/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:17:26 by psenko            #+#    #+#             */
/*   Updated: 2025/02/19 17:31:54 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*mv_lst_to_str(t_list **lst)
{
	t_list	*tmp_lst;
	char	*result_str;
	size_t	strsize;

	result_str = NULL;
	tmp_lst = *lst;
	strsize = 0;
	while (tmp_lst != NULL)
	{
		strsize += ft_strlen((char *)tmp_lst->content);
		tmp_lst = tmp_lst->next;
	}
	result_str = ft_calloc(strsize + 1, sizeof(char));
	if (result_str == NULL)
		return (free_list(lst), NULL);
	tmp_lst = *lst;
	while (tmp_lst != NULL)
	{
		ft_strlcat(result_str, (char *)tmp_lst->content, strsize + 1);
		tmp_lst = tmp_lst->next;
	}
	free_list(lst);
	return (result_str);
}

static char	*get_var(t_vars *vars, char **str)
{
	int		size;
	char	*new_str;
	char	*tmp_str;
	char	*env_val;

	new_str = NULL;
	tmp_str = NULL;
	env_val = NULL;
	size = 0;
	while (((*str)[size] != '$') && ((*str)[size] != '\0')
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
			// printf("%s\n", *str);
			(*str)++;
			// add_str_to_list(get_var(vars, str), &str_list);
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
	else if ((**str == '$') && (*((*str) + 1) == '?'))
	{
		new_str = ft_itoa(vars->return_code);
		(*str) += 2;
	}
	else if (**str == '$')
	{
		(*str)++;
		new_str = get_var(vars, str);
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

char	*handle_env_var(t_vars *vars, char *str)
{
	char	*new_str;
	t_list	*str_list;
	t_list	*tmplst;
	char	*result_str;

	str_list = NULL;
	new_str = NULL;
	tmplst = NULL;
	while (*str != '\0')
	{
		new_str = get_next_part(vars, &str);
		add_str_to_list(new_str, &str_list);
		// if (new_str != NULL)
		// {
		// 	tmplst = ft_lstnew(new_str);
		// 	ft_lstadd_back(&str_list, tmplst);
		// }
	}
	result_str = mv_lst_to_str(&str_list);
	// free_list(&str_list);
	return (result_str);
}

char	*handle_vars(t_vars *vars, char *instr)
{
	char	*tmp_str;

	tmp_str = NULL;
	if (ft_strchr(instr, '$'))
	{
		tmp_str = handle_env_var(vars, instr);
		free(instr);
		instr = tmp_str;
	}
	return (instr);
}
