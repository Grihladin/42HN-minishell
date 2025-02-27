/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:30:13 by psenko            #+#    #+#             */
/*   Updated: 2025/02/27 19:11:57 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
