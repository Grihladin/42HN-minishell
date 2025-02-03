/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:32:04 by mratke            #+#    #+#             */
/*   Updated: 2025/02/03 22:52:27 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	new_line_flag;

	new_line_flag = 1;
	i = 0;
	if (!args)
		return ;
	while (args[i] && !ft_strcmp(args[i], "-n"))
	{
		new_line_flag = 0;
		i++;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line_flag)
		printf("\n");
}
