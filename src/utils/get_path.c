/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:19:52 by psenko            #+#    #+#             */
/*   Updated: 2025/02/27 19:13:30 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_full_path(char *path, t_list *lstpath)
{
	char	*fullpath;
	char	*tmp;

	if (ft_strlen(path) < 1)
		return (NULL);
	if (ft_strchr(path, '/'))
		return (path);
	fullpath = NULL;
	while (lstpath != NULL)
	{
		tmp = ft_strjoin(lstpath->content, "/");
		if (tmp == NULL)
			return (NULL);
		fullpath = ft_strjoin(tmp, path);
		free(tmp);
		if (fullpath == NULL)
			return (NULL);
		if (access(fullpath, F_OK | X_OK) == 0)
			return (fullpath);
		if (fullpath != NULL)
			free(fullpath);
		lstpath = lstpath->next;
	}
	return (NULL);
}

// static void	ft_lstprint_paths(t_list *lst)
// {
// 	printf("PATH list:\n");
// 	ft_lstprint_str(lst);
// 	printf("\n");
// }

static char	*copy_next_path(char **str)
{
	char	*pathend;
	size_t	len;
	char	*path;

	len = 0;
	pathend = ft_strchr(*str, ':');
	if (pathend != NULL)
		len = pathend - *str;
	else
		len = ft_strlen(*str);
	path = ft_calloc(len + 1, 1);
	if (path == NULL)
		return (NULL);
	ft_strlcpy(path, *str, len + 1);
	*str += len;
	if (**str == ':')
		(*str)++;
	return (path);
}

int	get_paths(t_vars *vars)
{
	char	*pathstr;

	pathstr = find_var_env(vars->env_list, "PATH");
	if (pathstr != NULL)
	{
		while (*pathstr != '\0')
		{
			if (add_str_to_list(copy_next_path(&pathstr), &(vars->paths)) == -1)
				return (-1);
		}
	}
	return (0);
}
