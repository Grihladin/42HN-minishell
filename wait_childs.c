/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:48:36 by psenko            #+#    #+#             */
/*   Updated: 2025/02/26 18:06:24 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_childs(t_vars *vars)
{
	pid_t	pid;

	if (vars->cmnd_nmbrs)
	{
		pid = waitpid(vars->last_pid, &(vars->return_code), 0);
		(vars->cmnd_nmbrs)--;
		if (pid >= 0 && ((*(int *)&(vars->return_code)) & 0177) == 0)
			vars->return_code = (((*(int *)&(vars->return_code))
						>> 8) & 0x000000ff);
		else
		{
			vars->return_code = (((*(int *)&(vars->return_code))
						>> 8) & 0x000000ff);
			error_message(NULL, vars->return_code);
		}
		while (vars->cmnd_nmbrs)
		{
			pid = wait(NULL);
			(vars->cmnd_nmbrs)--;
		}
		set_signal_handler_parent(vars);
	}
	return (0);
}
