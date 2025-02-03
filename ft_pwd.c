/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:20:50 by mratke            #+#    #+#             */
/*   Updated: 2025/02/03 22:30:46 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env_list *env_list)
{
	char *pwd;

	pwd = find_var_env(env_list, "PWD");
	if (!pwd)
		return ;
	printf("%s\n", pwd);
}
