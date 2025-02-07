/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:38:40 by mratke            #+#    #+#             */
/*   Updated: 2025/02/07 20:14:00 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// dont test with && or || not implemented yet
int	main(int argc, char **argv, char **env)
{
	t_vars	vars;

	// char	**env_arr;
	if (!init(&vars, argc, argv, env))
	{
		wait_command(&vars);
	}
	// char	str[100] = "cat >> EOF | ";
	// t_list	*tokens;
	// t_node	*route;
	// tokens = tokenize(str);
	// print_list(tokens);
	// printf("\n");
	// env_arr = env_to_array(&vars);
	// free_arr_of_str(&env_arr);
	free_vars(&vars);
	return (0);
}
