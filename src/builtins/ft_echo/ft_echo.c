/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:32:04 by mratke            #+#    #+#             */
/*   Updated: 2025/02/26 15:31:33 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_line_check(char **args, int *i)
{
	int	j;
	int	new_line_flag;

	new_line_flag = 1;
	while (args[*i])
	{
		if (args[*i][0] != '-')
			break ;
		if (args[*i][1] != 'n')
			break ;
		j = 2;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] != '\0')
			break ;
		new_line_flag = 0;
		(*i)++;
	}
	return (new_line_flag);
}

int	ft_echo(char **args)
{
	int	i;
	int	new_line_flag;

	i = 1;
	if (!args || !args[1])
	{
		printf("\n");
		return (0);
	}
	new_line_flag = new_line_check(args, &i);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line_flag)
		printf("\n");
	return (0);
}
