/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:04:06 by psenko            #+#    #+#             */
/*   Updated: 2025/02/22 17:27:08 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_list_to_fd(t_list *str_list, int fd)
{
	t_list	*tmp;

	tmp = str_list;
	while (tmp != NULL)
	{
		ft_putendl_fd((char *)tmp->content, fd);
		tmp = tmp->next;
	}
}

int	here_doc(t_vars *vars, t_node *node, char expans)
{
	char	*tmpstr;
	t_list	*tmp;

	tmpstr = readline("> ");
	while ((tmpstr != NULL) && (ft_strncmp((node->command_args)[1], tmpstr,
			ft_strlen((node->command_args)[1])) != 0))
	{
		if (expans)
			tmpstr = handle_vars(vars, tmpstr);
		tmp = ft_lstnew(tmpstr);
		if (tmp == NULL)
			return (ft_lstclear(&tmp, free), 1);
		ft_lstadd_back(&(vars->here_doc_buf), tmp);
		tmpstr = readline("> ");
	}
	return (0);
}
