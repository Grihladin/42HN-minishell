/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:38:40 by mratke            #+#    #+#             */
/*   Updated: 2025/02/26 19:20:21 by mratke           ###   ########.fr       */
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
	return (vars.return_code);
}
