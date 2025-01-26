/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:51:07 by mratke            #+#    #+#             */
/*   Updated: 2024/10/08 11:06:53 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int ch)
{
	if (ch >= 'a' && ch <= 'z')
	{
		return (ch - 32);
	}
	return (ch);
}

// void	test_ft_toupper(void)
// {
// 	int	result;

// 	// Test case 1: Check if 'a' converts to 'A'
// 	result = ft_toupper('a');
// 	if (result == 'A')
// 		printf("Test case 1 passed!\n");
// 	else
// 		printf("Test case 1 failed!\n");

// 	// Test case 2: Check if 'z' converts to 'Z'
// 	result = ft_toupper('z');
// 	if (result == 'Z')
// 		printf("Test case 2 passed!\n");
// 	else
// 		printf("Test case 2 failed!\n");

// 	// Test case 3: Check if 'A' remains unchanged
// 	result = ft_toupper('A');
// 	if (result == 'A')
// 		printf("Test case 3 passed!\n");
// 	else
// 		printf("Test case 3 failed!\n");

// 	// Test case 4: Check if '0' (digit) remains unchanged
// 	result = ft_toupper('0');
// 	if (result == '0')
// 		printf("Test case 4 passed!\n");
// 	else
// 		printf("Test case 4 failed!\n");

// 	// Test case 5: Check if '@' (symbol) remains unchanged
// 	result = ft_toupper('@');
// 	if (result == '@')
// 		printf("Test case 5 passed!\n");
// 	else
// 		printf("Test case 5 failed!\n");

// 	// Test case 6: Check if ASCII -1 (EOF) remains unchanged
// 	result = ft_toupper(-1);
// 	if (result == -1)
// 		printf("Test case 6 passed!\n");
// 	else
// 		printf("Test case 6 failed!\n");
// }

// int	main(void)
// {
// 	test_ft_toupper();
// 	return (0);
// }
