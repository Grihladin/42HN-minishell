/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:16:14 by psenko            #+#    #+#             */
/*   Updated: 2025/02/07 13:57:43 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	execute_programm(t_vars *vars, char *cmnd, char **args, char **env)
// static int	execute_programm(t_vars *vars, char *cmnd, char *arg)
// {
// 	if (!ft_strcmp("echo", cmnd))
// 	{
// 		;
// 	}
// 	else if (!ft_strcmp("cd", cmnd))
// 	{
// 		ft_cd(vars, arg);
// 	}
// 	else if (!ft_strcmp("pwd", cmnd))
// 	{
// 		;
// 	}
// 	else if (!ft_strcmp("export", cmnd))
// 	{
// 		;
// 	}
// 	else if (!ft_strcmp("unset", cmnd))
// 	{
// 		;
// 	}
// 	else if (!ft_strcmp("exit", cmnd))
// 	{
// 		ft_exit();
// 	}
// 	return (0);
// }

int	execute_command(t_vars *vars, char *cmnd)
{
	// printf("Execute command: %s\n", cmnd);
	vars->tokens = tokenize(vars, cmnd);
	vars->node_list = parse_tokens(&(vars->tokens));
	print_tree(vars->node_list, 0);
	// execute_programm(vars, cmnd);
	free_list(&(vars->tokens));
	return (0);
}
