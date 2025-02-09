/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:34:28 by mratke            #+#    #+#             */
/*   Updated: 2025/02/09 23:04:03 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_str(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_str_merge(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	j = 0;
	i = 0;
	result = malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

char	*ft_strdup(const char *src)
{
	int		src_len;
	char	*dup;
	int		i;

	src_len = ft_strlen(src);
	dup = malloc((src_len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
