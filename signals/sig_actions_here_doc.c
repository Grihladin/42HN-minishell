/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_actions_here_doc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:17:34 by mratke            #+#    #+#             */
/*   Updated: 2025/02/27 16:37:39 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_received = 2;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

void	set_signal_heredoc(t_vars *vars)
{
	vars->sa.sa_handler = heredoc_handler;
	sigaction(SIGINT, &vars->sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
