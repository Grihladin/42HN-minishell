/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:59:19 by mratke            #+#    #+#             */
/*   Updated: 2024/10/11 12:59:08 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	i;

	i = 0;
	if (dest_size == 0)
	{
		return (ft_strlen(src));
	}
	while (i < dest_size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

// #include <string.h>

// int	main(void)
// {
// 	char	s2[5] = "zxcv";
// 	int		size;
// 	int		size1;
// 	char	s1[5] = "qwer";

// 	size1 = ft_strlcpy(s1, s2, 10);
// 	printf("%i\n", size1);
// 	for (int i = 0; i < 4; i++)
// 	{
// 		// size = ft_strlcpy(s1, s2, 2);
// 		// printf("%c %i\n", s1[i], size);
// 		printf("%c", s1[i]);
// 	}
// }
