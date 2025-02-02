/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:17:27 by psenko            #+#    #+#             */
/*   Updated: 2025/02/02 13:28:21 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_vars *vars)
{
	vars->env_list = NULL;
	vars->node_list = NULL;
	vars->operators = NULL;
	vars->paths = NULL;
	vars->tokens = NULL;
}
