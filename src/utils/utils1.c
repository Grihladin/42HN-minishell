/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:07:22 by psenko            #+#    #+#             */
/*   Updated: 2025/02/27 14:20:13 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_str_to_list(char *str, struct s_list **lst)
{
	t_list	*tmp;

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
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}

int	error_message(t_node *node, int error)
{
	if (error == 130 || error == 131 || error == 0)
		return (0);
	ft_putstr_fd(ERR_HEADER, 2);
	if (node && node->command_args && node->command_args[0])
	{
		ft_putstr_fd(node->command_args[0], 2);
		ft_putstr_fd(": ", 2);
	}
	if (error == ERR_NOT_FOUND)
		ft_putendl_fd("command not found", 2);
	else if (error == ERR_NO_PERM)
		ft_putendl_fd("permission denied", 2);
	else if (error == ERR_SYNTAX)
		ft_putendl_fd("syntax error", 2);
	else if (error == ERR_SYNTAX_NEAR)
		ft_putendl_fd("syntax error near unexpected token", 2);
	else
		ft_putendl_fd("error", 2);
	return (error);
}

char	*ft_strtolower(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(str);
	while (tmp[i])
	{
		tmp[i] = ft_tolower(tmp[i]);
		i++;
	}
	return (tmp);
}

void	clear_tree(t_node **root)
{
	if (*root == NULL)
		return ;
	clear_tree(&((*root)->left));
	clear_tree(&((*root)->right));
	free_double_array((*root)->command_args);
	(*root)->command_args = NULL;
	free_double_array((*root)->env);
	(*root)->env = NULL;
	delete_content((*root)->new_fds);
	delete_content((*root)->old_fds);
	delete_content(*root);
	*root = NULL;
}
