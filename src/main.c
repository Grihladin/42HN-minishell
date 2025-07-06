/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:38:40 by mratke            #+#    #+#             */
/*   Updated: 2025/02/27 18:56:46 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t	g_signal_received = 0;

int	main(int argc, char **argv, char **env)
{
	t_vars	vars;

	if (!init(&vars, argc, argv, env))
	{
		wait_command(&vars);
	}
	free_vars(&vars);
	return (vars.return_code);
}
