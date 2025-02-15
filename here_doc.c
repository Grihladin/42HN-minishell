/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:04:06 by psenko            #+#    #+#             */
/*   Updated: 2025/02/15 12:03:03 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc_fork(t_vars *vars, t_node *node, char **args)
{
	char	*tmpstr;

	vars->cmnd_nmbrs++;
	node->command_pid = fork();
	if (node->command_pid == 0)
	{
		tmpstr = get_next_line(0);
		while ((tmpstr != NULL) && (ft_strncmp(args[1], tmpstr,
					ft_strlen(args[1])) != 0))
		{
			write(1, tmpstr, ft_strlen(tmpstr));
			free(tmpstr);
			tmpstr = get_next_line(0);
		}
		delete_content(tmpstr);
		free_vars(vars);
		exit (0);
	}
	return (0);
}
