/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:25:31 by mratke            #+#    #+#             */
/*   Updated: 2024/10/07 21:12:43 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int ch)
{
	if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
	{
		return (1);
	}
	return (0);
}

// void	test_ft_isalpha(void)
// {
// 	int	result;

// 	// Test case 1: Check if 'A' is an alphabetic character (upper-case)
// 	result = ft_isalpha('A');
// 	if (result == 1)
// 		printf("Test case 1 passed!\n");
// 	else
// 		printf("Test case 1 failed!\n");

// 	// Test case 2: Check if '1' is not an alphabetic character (digit)
// 	result = ft_isalpha('1');
// 	if (result == 0)
// 		printf("Test case 2 passed!\n");
// 	else
// 		printf("Test case 2 failed!\n");

// 	// Test case 3: Check if 'z' is an alphabetic character (lower-case)
// 	result = ft_isalpha('z');
// 	if (result == 1)
// 		printf("Test case 3 passed!\n");
// 	else
// 		printf("Test case 3 failed!\n");

// 	// Test case 4: Check if '@' is not an alphabetic character (symbol)
// 	result = ft_isalpha('@');
// 	if (result == 0)
// 		printf("Test case 4 passed!\n");
// 	else
// 		printf("Test case 4 failed!\n");

// 	// Test case 5: Check if 'Z' is an alphabetic character (upper-case)
// 	result = ft_isalpha('Z');
// 	if (result == 1)
// 		printf("Test case 5 passed!\n");
// 	else
// 		printf("Test case 5 failed!\n");

// 	// Test case 6: Check if 'g' is an alphabetic character (lower-case)
// 	result = ft_isalpha('g');
// 	if (result == 1)
// 		printf("Test case 6 passed!\n");
// 	else
// 		printf("Test case 6 failed!\n");

// 	// Test case 7: Check if ASCII 65 ('A')
// 	//is an alphabetic character (upper-case)
// 	result = ft_isalpha(65);
// 	if (result == 1)
// 		printf("Test case 7 passed!\n");
// 	else
// 		printf("Test case 7 failed!\n");

// 	// Test case 8: Check if ASCII 122 ('z')
// 	//is an alphabetic character (lower-case)
// 	result = ft_isalpha(122);
// 	if (result == 1)
// 		printf("Test case 8 passed!\n");
// 	else
// 		printf("Test case 8 failed!\n");

// 	// Test case 9: Check if ASCII 64 ('@')
// 	//is not an alphabetic character
// 	result = ft_isalpha(64);
// 	if (result == 0)
// 		printf("Test case 9 passed!\n");
// 	else
// 		printf("Test case 9 failed!\n");

// 	// Test case 10: Check if ASCII 91 ('[')
// 	//is not an alphabetic character
// 	result = ft_isalpha(91);
// 	if (result == 0)
// 		printf("Test case 10 passed!\n");
// 	else
// 		printf("Test case 10 failed!\n");
// }

// int	main(void)
// {
// 	test_ft_isalpha();
// 	return (0);
// }
