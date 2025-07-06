/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:59:16 by psenko            #+#    #+#             */
/*   Updated: 2025/02/27 19:12:46 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_array(t_env_list	*env_lst)
{
	size_t		arr_size;
	char		**arr;
	char		**arrtmp;
	char		*tmpstr;

	arr_size = env_lstsize(env_lst);
	arr = ft_calloc(arr_size + 1, sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arrtmp = arr;
	while (env_lst != NULL)
	{
		if (env_lst->value != NULL)
		{
			tmpstr = ft_strjoin(env_lst->key, "=");
			*arrtmp = ft_strjoin(tmpstr, env_lst->value);
		}
		else
			tmpstr = ft_strdup(env_lst->key);
		free(tmpstr);
		arrtmp++;
		env_lst = env_lst->next;
	}
	*arrtmp = NULL;
	return (arr);
}
