/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:38:40 by mratke            #+#    #+#             */
/*   Updated: 2025/02/14 09:39:36 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// dont test with && or || not implemented yet
int	main(int argc, char **argv, char **env)
{
	t_vars	vars;

	if (!init(&vars, argc, argv, env))
	{
		wait_command(&vars);
	}
	return (0);
}
