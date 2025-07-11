/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:35:55 by mratke            #+#    #+#             */
/*   Updated: 2025/02/27 19:23:41 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char str)
{
	if ((str != '\0') && ((str == ' ') || (str == '\t') || (str == '\n')
			|| (str == '\v') || (str == '\f') || (str == '\r')))
		return (1);
	return (0);
}

char	*get_home(t_vars *vars)
{
	char	*new_str;
	char	*env_val;

	new_str = NULL;
	env_val = find_var_env(vars->env_list, "HOME");
	if (env_val != NULL)
		new_str = ft_strdup(env_val);
	return (new_str);
}

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

int	calculate_args(t_list *current)
{
	int	arg_count;

	arg_count = 0;
	while (current && !type_of_operator(current->content))
	{
		arg_count++;
		current = current->next;
	}
	return (arg_count);
}

char	**copy_lst_to_arr(t_list **lst)
{
	size_t	arr_size;
	t_list	*tmp_list;
	char	**result;
	char	**tmp_array;

	tmp_list = NULL;
	arr_size = ft_lstsize(*lst);
	result = ft_calloc(arr_size + 1, sizeof(char *));
	if (result == NULL)
		return (ft_lstclear(lst, free), NULL);
	tmp_list = *lst;
	tmp_array = result;
	while (tmp_list != NULL)
	{
		*tmp_array = tmp_list->content;
		tmp_array++;
		tmp_list->content = NULL;
		tmp_list = tmp_list->next;
	}
	*tmp_array = NULL;
	ft_lstclear(lst, free);
	return (result);
}
