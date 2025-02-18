/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:57:50 by psenko            #+#    #+#             */
/*   Updated: 2025/02/18 18:18:12 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_command(t_vars *vars)
{
	char	*cmnd;
	char	*line;
	int		exit_code;

	exit_code = vars->return_code;
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			cmnd = readline(PROMPT);
			if (!cmnd) // EOF (Ctrl+D)
				break ;
		}
		else
		{
			line = get_next_line(STDIN_FILENO);
			if (!line)
				break ;
			cmnd = ft_strtrim(line, "\n");
			free(line);
			if (!cmnd)
				break ;
		}
		if (*cmnd) // Only execute non-empty commands
		{
			execute_tree(vars, cmnd);
			exit_code = vars->return_code;
		}
		free(cmnd);
	}
	free_vars(vars);
	return (exit_code);
}
