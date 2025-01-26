/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:29:11 by mratke            #+#    #+#             */
/*   Updated: 2024/10/14 20:02:55 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	return ;
}

// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*new_node_1;
// 	t_list	*new_node_2;
// 	t_list	*new_node_3;
// 	t_list	*current;
// 	int		i;

// 	head = NULL;
// 	new_node_1 = ft_lstnew("Contetn of my new_node_1");
// 	ft_lstadd_front(&head, new_node_1);
// 	new_node_2 = ft_lstnew("Contetn of my new_node_2");
// 	ft_lstadd_front(&head, new_node_2);
// 	new_node_3 = ft_lstnew("Contetn of my new_node_3");
// 	ft_lstadd_front(&head, new_node_3);
// 	current = head;
// 	i = ft_lstsize(head);
// 	printf("lstsize = %i", i);
// 	while (current != NULL)
// 	{
// 		printf("number %i: %s\n", i, (char *)current->content);
// 		i++;
// 		current = current->next;
// 	}
// 	ft_lstclear(&head, free);
// }
