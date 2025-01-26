/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:49:15 by mratke            #+#    #+#             */
/*   Updated: 2024/10/14 20:27:33 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != NULL)
	{
		del(lst->content);
		free(lst);
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
// 	ft_lstdelone(new_node_2, free);
// 	printf("lstsize = %i", i);
// 	while (current != NULL)
// 	{
// 		printf("number %i: %s\n", i, (char *)current->content);
// 		i++;
// 		current = current->next;
// 	}
// }
