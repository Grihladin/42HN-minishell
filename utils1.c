/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:07:22 by psenko            #+#    #+#             */
/*   Updated: 2025/02/05 17:33:01 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_str_to_list(char *str, struct s_list **lst)
{
	t_list		*tmp;

	if (str == NULL)
		return (-1);
	if (*lst == NULL)
	{
		*lst = ft_lstnew(str);
		if (*lst == NULL)
			return (delete_content(str), -1);
	}
	else
	{
		tmp = ft_lstnew(str);
		if (tmp == NULL)
			return (free_list(lst), -1);
		ft_lstadd_back(lst, tmp);
	}
	return (0);
}

void	ft_lstprint_str(t_list *lst)
{
	while (lst != NULL)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}
