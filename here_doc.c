/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:04:06 by psenko            #+#    #+#             */
/*   Updated: 2025/02/26 17:28:49 by psenko           ###   ########.fr       */
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

static void	exit_here_doc(t_vars *vars, t_node *node)
{
	// sigaction(SIGINT, &(node->orig_int), NULL);
	// sigaction(SIGQUIT, &(node->orig_quit), NULL);
	set_signal_handler_parent(vars);
	restore_fds(&(node->old_fds));
	free_list(&(vars->here_doc_buf));
	g_signal_received = 0;
}

int	here_doc(t_vars *vars, t_node *node, char expans)
{
	char				*line;
	t_list				*tmp_lst;

	// sigaction(SIGINT, NULL, &(node->orig_int));
	// sigaction(SIGQUIT, NULL, &(node->orig_quit));
	set_signal_heredoc(vars);
	line = get_next_user_input(PROMPT_HERE_DOC);
	while (line && ft_strcmp((node->command_args)[1], line))
	{
		if (g_signal_received == 2)
		{
			// Delete printf
			// printf("here_doc_sig_int\n");
			free(line);
			exit_here_doc(vars, node);
			return (130);
		}
		if (expans)
			line = handle_vars_heredoc(vars, line);
		tmp_lst = ft_lstnew(line);
		if (tmp_lst == NULL)
		{
			free(line);
			exit_here_doc(vars, node);
			return (ft_lstclear(&tmp_lst, free), 1);
		}
		ft_lstadd_back(&(vars->here_doc_buf), tmp_lst);
		line = get_next_user_input(PROMPT_HERE_DOC);
	}
	write_list_to_fd(vars->here_doc_buf, STDOUT_FILENO);
	free_list(&(vars->here_doc_buf));
	free(line);
	exit_here_doc(vars, node);
	return (0);
}
