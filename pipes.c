/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:49:57 by psenko            #+#    #+#             */
/*   Updated: 2025/02/08 14:53:22 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*create_pipe(void)
{
	int		*p;

	p = ft_calloc(2, sizeof(int));
	if (p == NULL)
		return (-1);
	if (pipe(p))
		return (perror("Pipe create error"), free(p), -1);
	return (p);
}
