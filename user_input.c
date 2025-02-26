/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:36:02 by psenko            #+#    #+#             */
/*   Updated: 2025/02/26 09:49:48 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_user_input(char *prompt)
{
	char	*cmd;
	char	*line;

	cmd = NULL;
	line = NULL;
	if (isatty(STDIN_FILENO))
	{
		cmd = readline(prompt);
		return (cmd);
	}
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			return (line);
		cmd = ft_strtrim(line, "\n");
		free(line);
		return (cmd);
	}
	return (NULL);
}
