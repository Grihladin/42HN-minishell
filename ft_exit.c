/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:12:43 by mratke            #+#    #+#             */
/*   Updated: 2025/02/06 18:39:11 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// this function intended to work with combined command thats why i use args[1] because args in my head look like this |exit|arg|

int	ft_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	ft_putendl_fd("exit", 2);
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit(2);
		}
		exit_code = ft_atoi(args[1]);
		if (exit_code > 255)
			exit_code = exit_code % 256;
		if (args[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
	}
	exit((unsigned char)exit_code);
}
