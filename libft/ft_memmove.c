/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:36:52 by mratke            #+#    #+#             */
/*   Updated: 2024/10/10 20:09:45 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	if (d == s || count == 0)
		return (dest);
	if (d > s && d < s + count)
	{
		while (count > 0)
		{
			count--;
			d[count] = s[count];
		}
	}
	else
		ft_memcpy(d, s, count);
	return (dest);
}

// int	main(void)
// {
// 	char	src[] = "lorem ipsum dolor sit amet";
// 	char	*dest;
// 	int		arg;

// 	dest = src + 1;
// 	if (dest != ft_memmove(dest, src, 8))
// 		printf("dest's adress was not returned\n");
// 	else
// 	{
// 		for (size_t i = 0; i < 27; i++)
// 		{
// 			printf("%c", dest[i]);
// 		}
// 	}
// }
