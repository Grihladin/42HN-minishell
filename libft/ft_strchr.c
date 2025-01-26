/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:56:24 by mratke            #+#    #+#             */
/*   Updated: 2024/10/09 12:05:18 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	unsigned char	c;

	c = (unsigned char)ch;
	while (*str != '\0')
	{
		if (*str == c)
		{
			return ((char *)str);
		}
		str++;
	}
	if (c == '\0')
	{
		return ((char *)str);
	}
	return (NULL);
}

// void	test_ft_strchr(void)
// {
// 	char	*str;
// 	char	*result;

// 	str = "Hello, World!";
// 	// Test case 1: Find 'W'
// 	result = ft_strchr(str, 'W');
// 	if (result != NULL && *result == 'W')
// 		printf("Test case 1 passed! Found 'W'\n");
// 	else
// 		printf("Test case 1 failed!\n");
// 	// Test case 2: Find null terminator
// 	result = ft_strchr(str, '\0');
// 	if (result != NULL && *result == '\0')
// 		printf("Test case 2 passed! Found '\\0'\n");
// 	else
// 		printf("Test case 2 failed!\n");
// 	// Test case 3: Find character not in string
// 	result = ft_strchr(str, 'z');
// 	if (result == NULL)
// 		printf("Test case 3 passed! 'z' not found\n");
// 	else
// 		printf("Test case 3 failed!\n");
// }

// int	main(void)
// {
// 	test_ft_strchr();
// 	return (0);
// }
