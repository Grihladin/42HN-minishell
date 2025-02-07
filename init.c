/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:17:27 by psenko            #+#    #+#             */
/*   Updated: 2025/02/07 12:18:43 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init(t_vars *vars, int argc, char **argv, char **env)
{
	char	**args;
	char	**arggs;

	if ((argc == 0) || (argv == NULL))
		return (0);
	vars->env_list = NULL;
	vars->node_list = NULL;
	vars->operators = NULL;
	vars->paths = NULL;
	vars->tokens = NULL;
	set_sigs(vars);
	args = malloc(2 * sizeof(char *));
	args[0] = ft_strdup("ABCD=hi");
	args[1] = NULL;
	arggs = malloc(3 * sizeof(char *));
	arggs[0] = ft_strdup("-n");
	arggs[1] = ft_strdup("qwer");
	arggs[2] = NULL;
	create_env_list(&(vars->env_list), env);
	get_paths(vars);
	ft_export(vars->env_list, NULL);
	ft_export(vars->env_list, args);
	ft_export(vars->env_list, arggs);
	// printf("\n");
	ft_export(vars->env_list, NULL);
	// ft_pwd(vars->env_list);
	// ft_echo(arggs);
	// printf("\n\n\n");
	return (0);
}
