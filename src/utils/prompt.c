/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:57:50 by psenko            #+#    #+#             */
/*   Updated: 2025/02/27 19:17:34 by mratke           ###   ########.fr       */
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
