/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:57:50 by psenko            #+#    #+#             */
/*   Updated: 2025/02/18 23:09:30 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_command(t_vars *vars)
{
	char	*cmd;
	char	*line;
	int		exit_code;

	exit_code = vars->return_code;
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			cmd = readline(PROMPT);
			if (!cmd)
				break ;
		}
		else
		{
			line = get_next_line(STDIN_FILENO);
			if (!line)
				break ;
			cmd = ft_strtrim(line, "\n");
			free(line);
			if (!cmd)
				break ;
		}
		if (*cmd)
		{
			execute_tree(vars, cmd);
			exit_code = vars->return_code;
		}
		free(cmd);
	}
	return (free(vars), exit_code);
}
