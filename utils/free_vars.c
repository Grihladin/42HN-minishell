/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:53:39 by psenko            #+#    #+#             */
/*   Updated: 2025/02/27 19:13:08 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr_of_str(char ***strings)
{
	char		**strings1;

	strings1 = *strings;
	while (*strings1 != NULL)
	{
		free(*strings1);
		strings1++;
	}
	free(*strings);
}

void	free_list(t_list **lst)
{
	t_list	*nxt;

	while ((*lst) != NULL)
	{
		nxt = (*lst)->next;
		ft_lstdelone(*lst, delete_content);
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
	free_env(&(vars->env_list));
	free_list(&(vars->tokens));
	delete_content(vars->old_fds);
	vars->old_fds = NULL;
}

void	reset_vars(t_vars *vars)
{
	clear_tree(&(vars->node_list));
	free_list(&(vars->tokens));
	vars->im_in_pipe = 0;
}
