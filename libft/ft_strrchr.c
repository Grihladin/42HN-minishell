/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:20:53 by mratke            #+#    #+#             */
/*   Updated: 2024/10/09 11:59:18 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	unsigned char	c;
	char			*last_occurrence;

	last_occurrence = NULL;
	c = (unsigned char)ch;
	while (*str != '\0')
	{
		if (*str == c)
		{
			last_occurrence = (char *)str;
		}
		str++;
	}
	if (c == '\0')
	{
		return ((char *)str);
	}
	return (last_occurrence);
}

// void	test_ft_strrchr(void)
// {
// 	char	*str;
// 	char	*result;

// 	str = "Hello, World!";
// 	// Test case 1: Last occurrence of 'o'
// 	result = ft_strrchr(str, 'o');
// 	if (result != NULL && *result == 'o')
// 		printf("Test case 1 passed! Found 'o' at position: %ld\n", result
// 			- str);
// 	else
// 		printf("Test case 1 failed!\n");
// 	// Test case 2: Last occurrence of 'W'
// 	result = ft_strrchr(str, 'W');
// 	if (result != NULL && *result == 'W')
// 		printf("Test case 2 passed! Found 'W'\n");
// 	else
// 		printf("Test case 2 failed!\n");
// 	// Test case 3: Character not in string
// 	result = ft_strrchr(str, 'z');
// 	if (result == NULL)
// 		printf("Test case 3 passed! 'z' not found\n");
// 	else
// 		printf("Test case 3 failed!\n");
// 	// Test case 4: Search for null terminator
// 	result = ft_strrchr(str, '\0');
// 	if (result != NULL && *result == '\0')
// 		printf("Test case 4 passed! Found '\\0'\n");
// 	else
// 		printf("Test case 4 failed!\n");
// }

// int	main(void)
// {
// 	test_ft_strrchr();
// 	return (0);
// }
