/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:04:06 by psenko            #+#    #+#             */
/*   Updated: 2025/02/26 15:43:10 by mratke           ###   ########.fr       */
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
	char				*line;
	t_list				*tmp_lst;
	struct sigaction	orig_int;
	struct sigaction	orig_quit;

	sigaction(SIGINT, NULL, &orig_int);
	sigaction(SIGQUIT, NULL, &orig_quit);
	set_signal_heredoc();
	line = get_next_user_input(PROMPT_HERE_DOC);
	while (line && ft_strcmp((node->command_args)[1], line))
	{
		if (g_signal_received == 2)
		{
			free(line);
			sigaction(SIGINT, &orig_int, NULL);
			sigaction(SIGQUIT, &orig_quit, NULL);
			restore_fds(&(node->old_fds));
			return (130);
		}
		if (expans)
			line = handle_vars_heredoc(vars, line);
		tmp_lst = ft_lstnew(line);
		if (tmp_lst == NULL)
		{
			free(line);
			sigaction(SIGINT, &orig_int, NULL);
			sigaction(SIGQUIT, &orig_quit, NULL);
			return (ft_lstclear(&tmp_lst, free), 1);
		}
		ft_lstadd_back(&(vars->here_doc_buf), tmp_lst);
		line = get_next_user_input(PROMPT_HERE_DOC);
	}
	sigaction(SIGINT, &orig_int, NULL);
	sigaction(SIGQUIT, &orig_quit, NULL);
	restore_fds(&(node->old_fds));
	write_list_to_fd(vars->here_doc_buf, STDOUT_FILENO);
	free_list(&(vars->here_doc_buf));
	free(line);
	g_signal_received = 0;
	return (0);
}
