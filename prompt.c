/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:57:50 by psenko            #+#    #+#             */
/*   Updated: 2025/02/23 11:40:53 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_command(t_vars *vars)
{
	char	*cmd;
	char	*line;

	while (1)
	{
		cmd = NULL;
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
			execute_tree(vars, cmd);
		delete_content(cmd);
	}
	return (free_vars(vars), vars->return_code);
}
