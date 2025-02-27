/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:57:50 by psenko            #+#    #+#             */
/*   Updated: 2025/02/27 16:39:48 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_command(t_vars *vars)
{
	char	*cmd;

	while (1)
	{
		cmd = NULL;
		cmd = get_next_user_input(PROMPT);
		if ((cmd != NULL) && (*cmd))
			execute_tree(vars, cmd);
		if (cmd == NULL)
			break ;
		delete_content(cmd);
	}
	return (vars->return_code);
}
