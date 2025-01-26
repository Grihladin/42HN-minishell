/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:29:57 by mratke            #+#    #+#             */
/*   Updated: 2024/10/09 17:33:02 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *lhs, const char *rhs, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count && lhs[i] == rhs[i])
	{
		if (lhs[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	if (i == count)
	{
		return (0);
	}
	return ((unsigned char)lhs[i] - (unsigned char)rhs[i]);
}

// #include <string.h>

// void	test_ft_strncmp(void)
// {
// 	const char	*str1 = "hello";
// 	const char	*str2 = "hello";
// 	size_t		count;

// 	// Function prototype of ft_strncmp
// 	int ft_strncmp(const char *lhs, const char *rhs, size_t count);
// 	// Test 1: Both strings are identical and count
// is larger than the string length
// 	count = 10;
// 	printf("Test 1: %d (expected: %d)\n", ft_strncmp(str1, str2, count),
// 		strncmp(str1, str2, count));
// 	// Test 2: Both strings are identical,
// 	count = 3;
// 	printf("Test 2: %d (expected: %d)\n", ft_strncmp(str1, str2, count),
// 		strncmp(str1, str2, count));
// 	// Test 3: lhs is lexicographically smaller than rhs
// 	str1 = "abc";
// 	str2 = "abd";
// 	count = 3;
// 	printf("Test 3: %d (expected: %d)\n", ft_strncmp(str1, str2, count),
// 		strncmp(str1, str2, count));
// 	// Test 4: lhs is lexicographically larger than rhs
// 	str1 = "abd";
// 	str2 = "abc";
// 	count = 3;
// 	printf("Test 4: %d (expected: %d)\n", ft_strncmp(str1, str2, count),
// 		strncmp(str1, str2, count));
// 	// Test 5: Different lengths, but common prefix
// 	str1 = "hello";
// 	str2 = "hell";
// 	count = 5;
// 	printf("Test 5: %d (expected: %d)\n", ft_strncmp(str1, str2, count),
// 		strncmp(str1, str2, count));
// 	// Test 6: Different lengths, but comparison limited by count
// 	count = 4;
// 	printf("Test 6: %d (expected: %d)\n", ft_strncmp(str1, str2, count),
// 		strncmp(str1, str2, count));
// 	// Test 7: lhs is an empty string
// 	str1 = "";
// 	str2 = "test";
// 	count = 4;
// 	printf("Test 7: %d (expected: %d)\n", ft_strncmp(str1, str2, count),
// 		strncmp(str1, str2, count));
// 	// Test 8: rhs is an empty string
// 	str1 = "test";
// 	str2 = "";
// 	count = 4;
// 	printf("Test 8: %d (expected: %d)\n", ft_strncmp(str1, str2, count),
// 		strncmp(str1, str2, count));
// 	// Test 9: Both strings are empty
// 	str1 = "";
// 	str2 = "";
// 	count = 4;
// 	printf("Test 9: %d (expected: %d)\n", ft_strncmp(str1, str2, count),
// 		strncmp(str1, str2, count));
// 	// Test 10: Count is zero, should always return 0
// 	str1 = "abc";
// 	str2 = "xyz";
// 	count = 0;
// 	printf("Test 10: %d (expected: %d)\n", ft_strncmp(str1, str2, count),
// 		strncmp(str1, str2, count));
// }

// int	main(void)
// {
// 	test_ft_strncmp();
// 	return (0);
// }
