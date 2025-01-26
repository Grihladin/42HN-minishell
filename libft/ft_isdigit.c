/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:09:17 by mratke            #+#    #+#             */
/*   Updated: 2024/10/09 10:48:25 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return (1);
	}
	return (0);
}

// void	test_ft_isdigit(void)
// {
// 	int	result;

// 	// Test case 1: Check if '0' is a digit
// 	result = ft_isdigit('0');
// 	if (result == 1)
// 		printf("Test case 1 passed!\n");
// 	else
// 		printf("Test case 1 failed!\n");

// 	// Test case 2: Check if '5' is a digit
// 	result = ft_isdigit('5');
// 	if (result == 1)
// 		printf("Test case 2 passed!\n");
// 	else
// 		printf("Test case 2 failed!\n");

// 	// Test case 3: Check if '9' is a digit
// 	result = ft_isdigit('9');
// 	if (result == 1)
// 		printf("Test case 3 passed!\n");
// 	else
// 		printf("Test case 3 failed!\n");

// 	// Test case 4: Check if 'A' is not a digit (uppercase letter)
// 	result = ft_isdigit('A');
// 	if (result == 0)
// 		printf("Test case 4 passed!\n");
// 	else
// 		printf("Test case 4 failed!\n");

// 	// Test case 5: Check if 'a' is not a digit (lowercase letter)
// 	result = ft_isdigit('a');
// 	if (result == 0)
// 		printf("Test case 5 passed!\n");
// 	else
// 		printf("Test case 5 failed!\n");

// 	// Test case 6: Check if '+' is not a digit (symbol)
// 	result = ft_isdigit('+');
// 	if (result == 0)
// 		printf("Test case 6 passed!\n");
// 	else
// 		printf("Test case 6 failed!\n");

// 	// Test case 7: Check if ASCII 48 ('0') is a digit
// 	result = ft_isdigit(48);
// 	if (result == 1)
// 		printf("Test case 7 passed!\n");
// 	else
// 		printf("Test case 7 failed!\n");

// 	// Test case 8: Check if ASCII 57 ('9') is a digit
// 	result = ft_isdigit(57);
// 	if (result == 1)
// 		printf("Test case 8 passed!\n");
// 	else
// 		printf("Test case 8 failed!\n");

// 	// Test case 9: Check if ASCII 47 (one below '0') is not a digit
// 	result = ft_isdigit(47);
// 	if (result == 0)
// 		printf("Test case 9 passed!\n");
// 	else
// 		printf("Test case 9 failed!\n");

// 	// Test case 10: Check if ASCII 58 (one above '9') is not a digit
// 	result = ft_isdigit(58);
// 	if (result == 0)
// 		printf("Test case 10 passed!\n");
// 	else
// 		printf("Test case 10 failed!\n");
// }

// int	main(void)
// {
// 	test_ft_isdigit();
// 	return (0);
// }
