/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:55:12 by mratke            #+#    #+#             */
/*   Updated: 2024/10/09 19:33:07 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *lhs, const void *rhs, size_t count)
{
	unsigned char	*ptr_lhs;
	unsigned char	*ptr_rhs;
	size_t			i;

	ptr_lhs = (unsigned char *)lhs;
	ptr_rhs = (unsigned char *)rhs;
	i = 0;
	while (i < count)
	{
		if (ptr_lhs[i] == ptr_rhs[i])
		{
			i++;
		}
		else
		{
			return (ptr_lhs[i] - ptr_rhs[i]);
		}
	}
	return (0);
}

// int	main(void)
// {
// 	char	arr1[5] = "qwerx";
// 	char	arr2[5] = "qwert";

// 	printf("result: %i", ft_memcmp(arr1, arr2, 5));
// }
