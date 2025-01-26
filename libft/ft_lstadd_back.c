/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:49:52 by mratke            #+#    #+#             */
/*   Updated: 2024/10/14 19:48:32 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (new == NULL)
	{
		return ;
	}
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
	return ;
}
// HEAd --> NODE1 --> NODE2 --> NULL

// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*new_node_1;
// 	t_list	*new_node_2;
// 	t_list	*new_node_3;
// 	t_list	*new_node_4;
// 	t_list	*new_node_5;
// 	t_list	*current;
// 	int		i;

// 	head = NULL;
// 	new_node_1 = ft_lstnew("Contetn of my new_node_1");
// 	ft_lstadd_front(&head, new_node_1);
// 	new_node_2 = ft_lstnew("Contetn of my new_node_2");
// 	ft_lstadd_front(&head, new_node_2);
// 	new_node_3 = ft_lstnew("Contetn of my new_node_3");
// 	ft_lstadd_front(&head, new_node_3);
// 	new_node_4 = ft_lstnew("THIS MUST BE LAST");
// 	ft_lstadd_back(&head, new_node_4);
// 	new_node_5 = ft_lstnew("ONE MORE last one");
// 	ft_lstadd_back(&head, new_node_5);
// 	current = head;
// 	i = 1;
// 	while (current != NULL)
// 	{
// 		printf("number %i: %s\n", i, (char *)current->content);
// 		i++;
// 		current = current->next;
// 	}
// }
