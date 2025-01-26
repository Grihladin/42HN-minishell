/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:13:52 by mratke            #+#    #+#             */
/*   Updated: 2024/10/14 16:02:18 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst != NULL && new != NULL)
	{
		new->next = *lst;
		*lst = new;
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
// 	i = 1;
// 	while (current != NULL)
// 	{
// 		printf("number %i: %s\n", i, (char *)current->content);
// 		i++;
// 		current = current->next;
// 	}
