/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:01:56 by psenko            #+#    #+#             */
/*   Updated: 2025/02/07 11:31:02 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_sigs(t_vars *vars)
{
	sigemptyset(&(vars->sigaction.sa_mask));
	sigaddset(&(vars->sigaction.sa_mask), SIGINT);
	vars->sigaction.sa_handler = sig_handler;
	sigaction(SIGINT, &(vars->sigaction), NULL);
}
