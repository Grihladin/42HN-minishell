/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:24:58 by psenko            #+#    #+#             */
/*   Updated: 2025/02/27 18:54:47 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_next_command(char **str, t_list *lst)
{
	char	*tmp;
	size_t	len;
	char	*cmnd;

	len = 0;
	tmp = ft_strchr(*str, ' ');
	if (tmp != NULL)
		len = tmp - *str;
	else
		len = ft_strlen(*str);
	tmp = ft_calloc(len + 1, 1);
	if (tmp == NULL)
		return (NULL);
	ft_strlcpy(tmp, *str, len + 1);
	cmnd = get_full_path(tmp, lst);
	if (cmnd == NULL)
		return (tmp);
	free(tmp);
	return (cmnd);
}

static char	**copy_next_prms(char *str)
{
	char	**cmnd;

	cmnd = pip_split(str);
	if (cmnd == NULL)
		return (NULL);
	return (cmnd);
}
