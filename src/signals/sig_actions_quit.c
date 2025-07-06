/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_actions_quit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:17:34 by mratke            #+#    #+#             */
/*   Updated: 2025/02/27 16:37:43 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent_handler_quit(int signum)
{
	if (signum == SIGQUIT)
		ft_putstr_fd("^\\Quit\n", STDERR_FILENO);
}

void	set_signal_quit(t_vars *vars)
{
	vars->sa.sa_handler = parent_handler_quit;
	signal(SIGINT, SIG_IGN);
	sigaction(SIGQUIT, &vars->sa, NULL);
}
