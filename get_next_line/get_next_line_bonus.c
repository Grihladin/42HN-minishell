/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:37:53 by psenko            #+#    #+#             */
/*   Updated: 2024/11/09 16:23:12 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc_gnl(size_t nmemb)
{
	unsigned char		*arr;
	unsigned char		*arr1;
	size_t				len;

	len = nmemb + 1;
	arr = malloc(len);
	if (arr == NULL)
		return (NULL);
	arr1 = arr;
	while (len)
	{
		*arr1 = 0;
		arr1++;
		len--;
	}
	return (arr);
}

void	free_buff(t_buffer *st_buf, char all, int fd)
{
	t_buffer	*tmp_bf_nxt;

	while (st_buf->prv != NULL)
		st_buf = st_buf->prv;
	while (st_buf != NULL)
	{
		tmp_bf_nxt = st_buf->nxt;
		if ((all == 1) || (st_buf->fd == fd))
		{
			if (tmp_bf_nxt != NULL)
				tmp_bf_nxt->prv = st_buf->prv;
			if (st_buf->prv != NULL)
				st_buf->prv->nxt = tmp_bf_nxt;
			if ((st_buf->sz > 0) && (st_buf->dt != NULL))
				free(st_buf->dt);
			st_buf->sz = 0;
			st_buf->end = 0;
			st_buf->eof = 0;
			if (st_buf->fd != 0)
				free(st_buf);
		}
		st_buf = tmp_bf_nxt;
	}
}

size_t	ft_strlen_gnl(const char *s, size_t max)
{
	size_t		cnt;

	cnt = 0;
	if ((max > 0) && (s != NULL))
	{
		while ((s[cnt] != '\0') && (s[cnt] != '\n') && (max > 0))
		{
			cnt++;
			max--;
		}
	}
	return (cnt);
}

t_buffer	*get_buf(int fd, t_buffer *fst_bf)
{
	t_buffer	*tmp_bf;

	fst_bf->str = NULL;
	tmp_bf = fst_bf;
	while ((tmp_bf->nxt != NULL) && (tmp_bf->fd != fd))
		tmp_bf = tmp_bf->nxt;
	if (tmp_bf->fd != fd)
	{
		tmp_bf->nxt = ft_calloc_gnl(sizeof(struct s_buffer));
		if (tmp_bf->nxt == NULL)
			return (free_buff(tmp_bf, 1, tmp_bf->fd), NULL);
		tmp_bf->nxt->prv = tmp_bf;
		tmp_bf = tmp_bf->nxt;
		tmp_bf->fd = fd;
	}
	fst_bf->st_bf = tmp_bf;
	return (tmp_bf);
}

char	*get_next_line(int fd)
{
	static t_buffer		f_bf;

	if ((get_buf(fd, &f_bf) == NULL) || (read(fd, NULL, 0) < 0))
		return (free_buff(f_bf.st_bf, 0, f_bf.st_bf->fd), NULL);
	while ((f_bf.str == NULL) && (fd >= 0) && (BUFFER_SIZE > 0))
	{
		if (f_bf.st_bf->eof == 0)
		{
			if (incrs_stat_buf(f_bf.st_bf) == NULL)
				return (NULL);
			f_bf.rd = read(fd, (f_bf.st_bf->dt + f_bf.st_bf->end), BUFFER_SIZE);
			if ((f_bf.rd < BUFFER_SIZE) && (f_bf.rd >= 0))
				f_bf.st_bf->eof = 1;
			else if (f_bf.rd < 0)
				return (free_buff(f_bf.st_bf, 0, f_bf.st_bf->fd), NULL);
			f_bf.st_bf->end += f_bf.rd;
			if (gnl_strchr(f_bf.st_bf->dt, '\n', f_bf.st_bf->sz))
				f_bf.str = get_str_frm_buf(f_bf.st_bf);
		}
		else if ((f_bf.st_bf->eof == 1) && (f_bf.st_bf->end > 0))
			f_bf.str = get_str_frm_buf(f_bf.st_bf);
		else
			return (free_buff(f_bf.st_bf, 0, f_bf.st_bf->fd), NULL);
	}
	return (f_bf.str);
}
