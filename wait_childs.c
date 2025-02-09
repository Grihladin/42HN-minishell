/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:48:36 by psenko            #+#    #+#             */
/*   Updated: 2025/02/09 16:50:14 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_childs(int *cnt_chld)
{
	while (*cnt_chld)
	{
		wait(NULL);
		(*cnt_chld)--;
	}
	return (0);
}
