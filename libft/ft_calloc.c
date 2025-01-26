/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:03:21 by mratke            #+#    #+#             */
/*   Updated: 2024/10/10 19:04:18 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	unsigned char	*arr;
	size_t			i;

	arr = malloc(num * size);
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < num * size)
	{
		arr[i] = 0;
		i++;
	}
	return ((void *)arr);
}

// int	main(void)
// {
// 	int	*arr;

// 	arr = ft_calloc(5, sizeof(int));
// 	for (size_t i = 0; i < 100; i++)
// 	{
// 		printf("[%i] ", arr[i]);
// 	}
// }
