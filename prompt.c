/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:57:50 by psenko            #+#    #+#             */
/*   Updated: 2025/02/07 11:39:13 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_command(t_vars *vars)
{
	char	*cmnd;

	cmnd = NULL;
	while (1)
	{
		cmnd = readline(PROMPT);
		if (cmnd)
		{
			printf("Cmnd: %s\n", cmnd);
			add_history(cmnd);
			vars->tokens = tokenize(vars, cmnd);
			vars->node_list = parse_tokens(&(vars->tokens));
			print_tree(vars->node_list, 0);
			free_list(&(vars->tokens));
			free(cmnd);
			cmnd = NULL;
		}
		else
		{
			rl_on_new_line();
			rl_replace_line("exit\n", 0);
			rl_redisplay();
			break ;
		}
	}
	return (0);
}
