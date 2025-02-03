/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:53:39 by psenko            #+#    #+#             */
/*   Updated: 2025/02/03 20:11:11 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_content(void *n)
{
	if (n != NULL)
		free(n);
}

void	free_split(char **strings)
{
	char		**strings1;

	strings1 = strings;
	while (*strings1 != NULL)
	{
		free(*strings1);
		strings1++;
	}
}

void	free_splitted_list(t_list **lst)
{
	t_list	*nxt;

	while (*lst != NULL)
	{
		nxt = (*lst)->next;
		free_split((char **)(*lst)->content);
		ft_lstdelone(*lst, &delete_content);
		*lst = nxt;
	}
	*lst = NULL;
}

void	free_list(t_list **lst)
{
	t_list	*nxt;

	while (*lst != NULL)
	{
		nxt = (*lst)->next;
		ft_lstdelone(*lst, &delete_content);
		*lst = nxt;
	}
	*lst = NULL;
}

static void	free_env(t_env_list **env)
{
	t_env_list	*nxt;

	while (*env != NULL)
	{
		nxt = (*env)->next;
		delete_content((*env)->key);
		delete_content((*env)->value);
		free(*env);
		*env = nxt;
	}
}

void	free_vars(t_vars *vars)
{
	// struct s_list	*tmp;
	free_env(&(vars->env_list));
	free_list(&(vars->tokens));

	// free_list(&(lists->paths));
	// free_list(&(lists->cmndlst));
	// free_splitted_list(&(lists->prmslst));
	// delete_content(lists->limiter);
	// lists->limiter = NULL;
	// tmp = lists->ppslst;
	// while (tmp != NULL && tmp->content != NULL)
	// {
	// 	close(((int *)tmp->content)[0]);
	// 	close(((int *)tmp->content)[1]);
	// 	tmp = tmp->next;
	// }
	// free_list(&(lists->ppslst));
}
