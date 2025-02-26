/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:04:06 by psenko            #+#    #+#             */
/*   Updated: 2025/02/26 09:49:15 by psenko           ###   ########.fr       */
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

int	here_doc(t_vars *vars, t_node *node, char expans)
{
	char	*line;
	t_list	*tmp_lst;
	int		mark_len;

	mark_len = ft_strlen((node->command_args)[1]);
	line = get_next_user_input(PROMPT_HERE_DOC);
	while (line && ft_strncmp((node->command_args)[1], line, mark_len))
	{
		if (expans)
			line = handle_vars_heredoc(vars, line);
		tmp_lst = ft_lstnew(line);
		if (tmp_lst == NULL)
			return (ft_lstclear(&tmp_lst, free), 1);
		ft_lstadd_back(&(vars->here_doc_buf), tmp_lst);
		line = get_next_user_input(PROMPT_HERE_DOC);
	}
	restore_fds(&(node->old_fds));
	write_list_to_fd(vars->here_doc_buf, STDOUT_FILENO);
	free_list(&(vars->here_doc_buf));
	return (0);
}
