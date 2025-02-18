/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:48:36 by psenko            #+#    #+#             */
/*   Updated: 2025/02/18 17:23:59 by psenko           ###   ########.fr       */
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
		if (pid >= 0 && WIFEXITED(vars->return_code))
		{
			vars->return_code = WEXITSTATUS(vars->return_code);
			// printf("PID %d return (code %d\n", pid, vars->return_code));
		}
		else
		{
			vars->return_code = 1;
			error_message(NULL, 1);
		}
		while (vars->cmnd_nmbrs)
		{
			pid = wait(&(vars->return_code));
			(vars->cmnd_nmbrs)--;
		}
	}
	return (0);
}
