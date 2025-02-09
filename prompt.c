/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:57:50 by psenko            #+#    #+#             */
/*   Updated: 2025/02/09 23:06:06 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_command(t_vars *vars)
{
	char	*cmnd;
	char	*line;

	cmnd = NULL;
	while (1)
	{
		// cmnd = readline(PROMPT);
		if (isatty(fileno(stdin)))
			cmnd = readline(PROMPT);
		else
		{
			line = get_next_line(fileno(stdin));
			cmnd = ft_strtrim(line, "\n");
			free(line);
		}
		if (cmnd)
		{
			execute_tree(vars, cmnd);
			free(cmnd);
			cmnd = NULL;
		}
		else
		{
			// rl_replace_line("exit", 0);
			write(0, "exit\n", 5);
			// rl_on_new_line();
			// rl_redisplay();
			// rl_replace_line("SOme text", 0);
			// rl_redisplay();
			// continue ;
			break ;
		}
	}
	return (0);
}
