/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:03:50 by mratke            #+#    #+#             */
/*   Updated: 2024/10/11 12:38:59 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dest_size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	size_to_copy;
	size_t	i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dest_size <= dest_len)
		return (dest_size + src_len);
	size_to_copy = dest_size - dest_len - 1;
	i = 0;
	while (i < size_to_copy && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}

// #include <string.h>

// int	main(void)
// {
// 	char	destination[50] = "Hello, ";
// 	char	source[10] = "World!";
// 	size_t	result;
// 	size_t	result1;

// 	result = ft_strlcat(destination, source, sizeof(destination));
// 	printf("Concatenated String: %s\n", destination);
// 	printf("Result Length: %zu\n", result);
// 	printf("Result Length: %i\n", ft_strlen(destination));
// }
