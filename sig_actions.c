/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:01:56 by psenko            #+#    #+#             */
/*   Updated: 2025/02/26 18:20:45 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent_handler(int signum)
{
	g_signal_received = signum;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	child_handler(int signum)
{
	if (signum == SIGINT)
		exit(130);
	else if (signum == SIGQUIT)
		exit(131);
}

void	set_signal_handler_parent(t_vars *vars)
{
	vars->sa.sa_handler = parent_handler;
	sigaction(SIGINT, &vars->sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals(t_vars *vars)
{
	tcgetattr(STDIN_FILENO, &vars->term);
	vars->term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &vars->term);
	vars->sa.sa_handler = parent_handler;
	sigemptyset(&vars->sa.sa_mask);
	vars->sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &vars->sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_child(t_vars *vars)
{
	vars->sa.sa_handler = child_handler;
	sigemptyset(&vars->sa.sa_mask);
	vars->sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &vars->sa, NULL);
	sigaction(SIGQUIT, &vars->sa, NULL);
}
