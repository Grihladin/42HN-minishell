/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:48:36 by psenko            #+#    #+#             */
/*   Updated: 2025/02/15 12:55:05 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_childs(t_vars *vars)
{
	pid_t	pid;
	while (vars->cmnd_nmbrs)
	{
		// Need to handle return code
		pid = wait(&(vars->return_code));
		if (pid >= 0 && WIFEXITED(vars->return_code))
		{
			vars->return_code = WEXITSTATUS(vars->return_code);
			printf("PID %d return code %d\n", pid, vars->return_code);
		}
		(vars->cmnd_nmbrs)--;
	}
	return (0);
}
