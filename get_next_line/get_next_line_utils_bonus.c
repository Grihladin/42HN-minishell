/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:37:50 by psenko            #+#    #+#             */
/*   Updated: 2024/11/08 18:33:41 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_memcpy_gnl(const void *src, size_t size, size_t n)
{
	char			*dest_ch;
	const char		*src_ch;
	char			*new_str;

	new_str = ft_calloc_gnl(size + BUFFER_SIZE);
	if ((new_str == NULL) || (src == NULL))
		return (new_str);
	dest_ch = new_str;
	src_ch = src;
	while (n)
	{
		*dest_ch = *src_ch;
		dest_ch++;
		src_ch++;
		n--;
	}
	return (new_str);
}

t_buffer	*incrs_stat_buf(t_buffer *st_buf)
{
	char	*tmp_str;

	tmp_str = NULL;
	tmp_str = ft_memcpy_gnl(st_buf->dt, st_buf->sz, st_buf->end);
	if (tmp_str == NULL)
		return (free_buff(st_buf, 1, st_buf->fd), NULL);
	if ((st_buf->sz) > 0)
		free(st_buf->dt);
	st_buf->dt = tmp_str;
	st_buf->sz += BUFFER_SIZE;
	return (st_buf);
}

char	gnl_strchr(const char *str, char c, size_t sz)
{
	if (str != NULL)
	{
		while ((sz > 0) && ((*str != c)))
		{
			str++;
			sz--;
		}
		if (*str == c)
			return (1);
	}
	return (0);
}

char	*gnl_strcpy(const char *src, size_t len)
{
	char	*dst;
	char	*dst1;

	dst = ft_calloc_gnl(len + 1);
	if (dst == NULL)
		return (NULL);
	dst1 = dst;
	while ((*src != '\n') && (*src != '\0'))
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = *src;
	return (dst1);
}

char	*get_str_frm_buf(t_buffer *st_buf)
{
	char		*str;
	char		*ndt;
	size_t		len;
	size_t		nsz;

	str = gnl_strcpy(st_buf->dt, ft_strlen_gnl(st_buf->dt, st_buf->end));
	if (str == NULL)
		return (free_buff(st_buf, 1, st_buf->fd), NULL);
	len = ft_strlen_gnl(st_buf->dt, st_buf->end);
	len += gnl_strchr(st_buf->dt, '\n', st_buf->sz);
	nsz = st_buf->sz - len - (st_buf->sz - st_buf->end);
	if (nsz > 0)
	{
		ndt = ft_memcpy_gnl((st_buf->dt + len), nsz, (st_buf->end - len));
		if (ndt == NULL)
			free_buff(st_buf, 1, st_buf->fd);
		st_buf->end = st_buf->end - len;
		if (st_buf->sz > 0)
			free(st_buf->dt);
		st_buf->dt = ndt;
		st_buf->sz = nsz;
	}
	else
		free_buff(st_buf, 0, st_buf->fd);
	return (str);
}
