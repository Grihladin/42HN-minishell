/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:16:22 by mratke            #+#    #+#             */
/*   Updated: 2024/10/14 22:18:09 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result_head;
	t_list	*current;
	t_list	*new_node;
	void	*new_content;

	result_head = NULL;
	current = lst;
	while (current != NULL)
	{
		new_content = f(current->content);
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
		{
			del(new_content);
			ft_lstclear(&result_head, del);
			return (NULL);
		}
		ft_lstadd_back(&result_head, new_node);
		current = current->next;
	}
	return (result_head);
}
