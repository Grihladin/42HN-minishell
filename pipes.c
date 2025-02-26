/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:49:57 by psenko            #+#    #+#             */
/*   Updated: 2025/02/26 17:32:08 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_fds(int **fd)
{
	(*fd)[0] = dup(STDIN_FILENO);
	(*fd)[1] = dup(STDOUT_FILENO);
	return (0);
}

int	restore_fds(int **fd)
{
	if ((*fd)[0] != -1)
	{
		dup2((*fd)[0], STDIN_FILENO);
		close((*fd)[0]);
		(*fd)[0] = -1;
	}
	if ((*fd)[1] != -1)
	{
		dup2((*fd)[1], STDOUT_FILENO);
		close((*fd)[1]);
		(*fd)[1] = -1;
	}
	return (0);
}

int	close_fds(int **fd)
{
	if ((*fd)[0] > -1)
	{
		close((*fd)[0]);
		(*fd)[0] = -1;
	}
	if ((*fd)[1] > -1)
	{
		close((*fd)[1]);
		(*fd)[1] = -1;
	}
	return (0);
}

int	create_pipe(int **p)
{
	if (pipe(*p))
		return (perror("Pipe create error"), -1);
	return (0);
}

int	reset_stdio(t_vars *vars)
{
	dup2(vars->fd_stdin, STDIN_FILENO);
	dup2(vars->fd_stdout, STDOUT_FILENO);
	return (0);
}
