/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:04:06 by psenko            #+#    #+#             */
/*   Updated: 2025/02/15 14:40:39 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_list_to_fd(t_list *str_list, int fd)
{
	t_list	*tmp;

	tmp = str_list;
	while (tmp != NULL)
	{
		write(fd, (char *)tmp->content, ft_strlen((char *)tmp->content));
		tmp = tmp->next;
	}
}

t_list	*here_doc(t_vars *vars, t_node *node, char **args)
{
	char	*tmpstr;
	t_list	*str_list;
	t_list	*tmp;

	str_list = NULL;
	vars->cmnd_nmbrs++;
	vars->cmnd_nmbrs--;
	node->command_pid = node->command_pid;
	// node->command_pid = fork();
	// if (node->command_pid == 0)
	// write(1, "st > ", 5);
	tmpstr = get_next_line(0);
	while ((tmpstr != NULL) && (ft_strncmp(args[1], tmpstr,
				ft_strlen(args[1])) != 0))
	{
		tmp = ft_lstnew(tmpstr);
		if (tmp == NULL)
			return (ft_lstclear(&tmp, free), NULL);
		ft_lstadd_back(&str_list, tmp);
		// free(tmpstr);
		// write(1, "> ", 2);
		tmpstr = get_next_line(0);
	}
	// delete_content(tmpstr);
	// free_vars(vars);
	// exit(0);
	return (str_list);
}
