/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:59:16 by psenko            #+#    #+#             */
/*   Updated: 2025/02/05 17:56:43 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_arr_of_str(char **arr)
{
	char		**strings;

	strings = arr;
	while (*strings != NULL)
	{
		printf("%s\n", *strings);
		strings++;
	}
}

char	**env_to_array(t_vars *vars)
{
	t_env_list	*env_lst;
	size_t		arr_size;
	char		**arr;
	char		**arrtmp;
	char		*tmpstr;

	env_lst = vars->env_list;
	arr_size = env_lstsize(env_lst);
	arr = ft_calloc(arr_size + 1, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arrtmp = arr;
	while (env_lst != NULL)
	{
		tmpstr = ft_strjoin(env_lst->key, "=");
		*arrtmp = ft_strjoin(tmpstr, env_lst->value);
		free(tmpstr);
		arrtmp++;
		env_lst = env_lst->next;
	}
	*arrtmp = NULL;
	print_arr_of_str(arr);
	return (arr);
}
