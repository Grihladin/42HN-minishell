/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:04:06 by psenko            #+#    #+#             */
/*   Updated: 2025/02/15 16:13:34 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_list_to_fd(t_list *str_list, int fd)
{
	t_list	*tmp;

	tmp = str_list;
	while (tmp != NULL)
	{
		ft_putendl_fd((char *)tmp->content, fd);
		tmp = tmp->next;
	}
}

int	here_doc(t_vars *vars, t_node *node, char **args)
{
	char	*tmpstr;
	t_list	*tmp;

	vars->cmnd_nmbrs++;
	vars->cmnd_nmbrs--;
	node->command_pid = node->command_pid;
	// node->command_pid = fork();
	// if (node->command_pid == 0)
	// tmpstr = get_next_line(0);
	tmpstr = readline("> ");
	while ((tmpstr != NULL) && (ft_strncmp(args[1], tmpstr,
				ft_strlen(args[1])) != 0))
	{
		tmp = ft_lstnew(tmpstr);
		if (tmp == NULL)
			return (ft_lstclear(&tmp, free), 1);
		ft_lstadd_back(&(vars->here_doc_buf), tmp);
		// free(tmpstr);
		tmpstr = readline("> ");
	}
	// delete_content(tmpstr);
	// free_vars(vars);
	// exit(0);
	return (0);
}
