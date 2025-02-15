/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:37:56 by psenko            #+#    #+#             */
/*   Updated: 2024/11/17 14:01:18 by psenko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_buffer
{
	char			*dt;
	size_t			end;
	size_t			sz;
	int				eof;
	int				fd;
	ssize_t			rd;
	struct s_buffer	*st_bf;
	struct s_buffer	*nxt;
	struct s_buffer	*prv;
	char			*str;
}			t_buffer;

char		*get_next_line(int fd);
void		free_buff(t_buffer *st_buf, char all, int fd);
char		gnl_strchr(const char *str, char c, size_t sz);
size_t		ft_strlen_gnl(const char *s, size_t max);
t_buffer	*incrs_stat_buf(t_buffer *stat_buff);
t_buffer	*get_buf(int fd, t_buffer *fst_bf);
char		*get_str_frm_buf(t_buffer *stat_buff);
void		*ft_calloc_gnl(size_t nmemb);

#endif
