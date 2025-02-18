/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:24:58 by psenko            #+#    #+#             */
/*   Updated: 2025/02/18 17:21:43 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// static void	ft_lstprint_commands(t_list *lst)
// {
// 	ft_printf("Commands list:\n");
// 	ft_lstprint_str(lst);
// 	ft_printf("\n");
// }

// static void	ft_lstprint_params(t_list *lst)
// {
// 	ft_printf("Params list:\n");
// 	ft_lstprint_split(lst);
// 	ft_printf("\n");
// }

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

// int	get_commands(int argc, char **argv, struct s_lists *lists)
// {
// 	char	*tmp;
// 	int		ind;

// 	tmp = NULL;
// 	ind = 2;
// 	while (ind < (argc - 1))
// 	{
// 		if (lists->here_doc && ind == 2)
// 		{
// 			tmp = ft_strdup(argv[ind]);
// 			if (add_str_to_list(tmp, &(lists->cmndlst)) == -1)
// 				return (-1);
// 		}
// 		else
// 		{
// 			tmp = argv[ind];
// 			if (add_str_to_list(copy_next_command(&tmp, lists->paths),
// 					&(lists->cmndlst)) == -1)
// 				return (-1);
// 		}
// 		if (add_split_to_list(copy_next_prms(tmp), &(lists->prmslst)) == -1)
// 			return (-1);
// 		ind++;
// 	}
// 	return (0);
// }

	// ft_lstprint_commands(lists->cmndlst);
	// ft_lstprint_params(lists->prmslst);
