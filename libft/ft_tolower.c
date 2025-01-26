/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:07:54 by mratke            #+#    #+#             */
/*   Updated: 2024/10/08 11:10:48 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int ch)
{
	if (ch >= 'A' && ch <= 'Z')
	{
		return (ch + 32);
	}
	return (ch);
}

// void	test_ft_tolower(void)
// {
// 	int	result;

// 	// Test case 1: Check if 'A' converts to 'a'
// 	result = ft_tolower('A');
// 	if (result == 'a')
// 		printf("Test case 1 passed!\n");
// 	else
// 		printf("Test case 1 failed!\n");

// 	// Test case 2: Check if 'Z' converts to 'z'
// 	result = ft_tolower('Z');
// 	if (result == 'z')
// 		printf("Test case 2 passed!\n");
// 	else
// 		printf("Test case 2 failed!\n");

// 	// Test case 3: Check if 'a' remains unchanged
// 	result = ft_tolower('a');
// 	if (result == 'a')
// 		printf("Test case 3 passed!\n");
// 	else
// 		printf("Test case 3 failed!\n");

// 	// Test case 4: Check if 'z' remains unchanged
// 	result = ft_tolower('z');
// 	if (result == 'z')
// 		printf("Test case 4 passed!\n");
// 	else
// 		printf("Test case 4 failed!\n");

// 	// Test case 5: Check if '0' (digit) remains unchanged
// 	result = ft_tolower('0');
// 	if (result == '0')
// 		printf("Test case 5 passed!\n");
// 	else
// 		printf("Test case 5 failed!\n");

// 	// Test case 6: Check if '@' (symbol) remains unchanged
// 	result = ft_tolower('@');
// 	if (result == '@')
// 		printf("Test case 6 passed!\n");
// 	else
// 		printf("Test case 6 failed!\n");

// 	// Test case 7: Check if ASCII -1 (EOF) remains unchanged
// 	result = ft_tolower(-1);
// 	if (result == -1)
// 		printf("Test case 7 passed!\n");
// 	else
// 		printf("Test case 7 failed!\n");
// }

// int	main(void)
// {
// 	test_ft_tolower();
// 	return (0);
// }
