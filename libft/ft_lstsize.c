/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:52:20 by mratke            #+#    #+#             */
/*   Updated: 2024/10/14 19:11:20 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*current;

	i = 0;
	current = lst;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
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
// }
