/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:56:37 by mratke            #+#    #+#             */
/*   Updated: 2024/10/09 18:25:49 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int ch, size_t count)
{
	size_t			i;
	unsigned char	c;
	unsigned char	*p;

	p = (unsigned char *)ptr;
	i = 0;
	c = (unsigned char)ch;
	while (i < count)
	{
		if (p[i] == c)
		{
			return ((void *)&p[i]);
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	*arr;

// 	arr = malloc(5 * sizeof(char));
// 	ft_memset(arr, 'b', 1);
// 	printf("memchr: %s", ft_memchr(arr, 'b', 5));
// }
