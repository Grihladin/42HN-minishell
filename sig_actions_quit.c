/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_actions_quit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:17:34 by mratke            #+#    #+#             */
/*   Updated: 2025/02/26 18:08:10 by psenko           ###   ########.fr       */
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
	// sigaction(SIGINT, &vars->sa, NULL);
	signal(SIGINT, SIG_IGN);
	sigaction(SIGQUIT, &vars->sa, NULL);
}
