/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:51:50 by psenko            #+#    #+#             */
/*   Updated: 2025/02/26 14:13:10 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	close_all_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < MAX_FD)
	{
		close(fd);
		fd++;
	}
	return (0);
}

static char	*get_next_part(char **str)
{
	int		size;
	char	*new_str;

	new_str = NULL;
	size = 0;
	while (((*str)[size] != '\'') && ((*str)[size] != '\0')
			&& ((*str)[size] != '"'))
		size++;
	new_str = ft_calloc(size + 1, 1);
	ft_strlcpy(new_str, *str, size + 1);
	*str += size;
	return (new_str);
}

char	*delete_quotes(char *str)
{
	char	*tmp;
	char	*new_str;
	t_list	*str_list;
	char	*result_str;

	tmp = str;
	str_list = NULL;
	while (*tmp != '\0')
	{
		while ((*tmp == '\'') || (*tmp == '"'))
			tmp++;
		new_str = get_next_part(&tmp);
		add_str_to_list(new_str, &str_list);
	}
	result_str = mv_lst_to_str(&str_list);
	free(str);
	return (result_str);
}

int	type_of_operator(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<")
		|| !ft_strcmp(str, "<<"))
		return (REDIRECT_TYPE);
	else if (!ft_strcmp(str, "|"))
		return (PIPE_TYPE);
	else if (!ft_strcmp(str, "&&"))
		return (AND_TYPE);
	else if (!ft_strcmp(str, "||"))
		return (OR_TYPE);
	return (COMMAND_TYPE);
}
