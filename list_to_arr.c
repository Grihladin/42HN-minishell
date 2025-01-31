/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:30:13 by psenko            #+#    #+#             */
/*   Updated: 2025/01/31 17:45:42 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_lst_to_arr(t_list **lst)
{
	size_t	arr_size;
	t_list	*tmplst;
	char	**arr;
	char	**arrtmp;

	tmplst = NULL;
	arr_size = ft_lstsize(*lst);
	arr = ft_calloc(arr_size + 1, sizeof(char *));
	if (arr == NULL)
		return (ft_lstclear(lst, free), NULL);
	tmplst = *lst;
	arrtmp = arr;
	while (tmplst != NULL)
	{
		*arrtmp = tmplst->content;
		arrtmp++;
		tmplst->content = NULL;
		tmplst = tmplst->next;
	}
	*arrtmp = NULL;
	ft_lstclear(lst, free);
	return (arr);
}
