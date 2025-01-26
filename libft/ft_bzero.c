/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:37:33 by mratke            #+#    #+#             */
/*   Updated: 2024/10/10 18:57:46 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

// int	main(void)
// {
// 	char	*arr;

// 	arr = malloc(10 * (sizeof(void)));
// 	bzero(arr, 10);
// 	for (size_t i = 0; i < 10; i++)
// 	{
// 		printf("[%c] ", arr[i]);
// 	}
// 	printf("\n");
// 	for (size_t i = 0; i < 10; i++)
// 	{
// 		printf("[%i] ", arr[i]);
// 	}
// }
