/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:20:50 by mratke            #+#    #+#             */
/*   Updated: 2025/02/18 22:30:00 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_env_list *env_list)
{
	char	*pwd;
	char	*current_dir;

	pwd = find_var_env(env_list, "PWD");
	if (!pwd)
	{
		current_dir = getcwd(NULL, 0);
		if (!current_dir)
			return (1);
		if (printf("%s\n", current_dir) < 0)
			return (free(current_dir), 1);
		return (free(current_dir), 0);
	}
	if (printf("%s\n", pwd) < 0)
		return (1);
	return (0);
}
