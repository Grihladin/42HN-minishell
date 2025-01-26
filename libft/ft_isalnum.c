/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:12:01 by mratke            #+#    #+#             */
/*   Updated: 2024/10/08 11:35:48 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int ch)
{
	if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z')
		|| (ch >= 'A' && ch <= 'Z'))
	{
		return (1);
	}
	return (0);
}

// void	test_ft_isalnum(void)
// {
// 	int	result;

// 	// Test case 1: Check if 'a' is alphanumeric (lowercase)
// 	result = ft_isalnum('a');
// 	if (result == 1)
// 		printf("Test case 1 passed!\n");
// 	else
// 		printf("Test case 1 failed!\n");

// 	// Test case 2: Check if 'Z' is alphanumeric (uppercase)
// 	result = ft_isalnum('Z');
// 	if (result == 1)
// 		printf("Test case 2 passed!\n");
// 	else
// 		printf("Test case 2 failed!\n");

// 	// Test case 3: Check if '0' is alphanumeric (digit)
// 	result = ft_isalnum('0');
// 	if (result == 1)
// 		printf("Test case 3 passed!\n");
// 	else
// 		printf("Test case 3 failed!\n");

// 	// Test case 4: Check if '@' is not alphanumeric (symbol)
// 	result = ft_isalnum('@');
// 	if (result == 0)
// 		printf("Test case 4 passed!\n");
// 	else
// 		printf("Test case 4 failed!\n");

// 	// Test case 5: Check if '9' is alphanumeric (digit)
// 	result = ft_isalnum('9');
// 	if (result == 1)
// 		printf("Test case 5 passed!\n");
// 	else
// 		printf("Test case 5 failed!\n");

// 	// Test case 6: Check if ASCII -1 (EOF) is not alphanumeric
// 	result = ft_isalnum(-1);
// 	if (result == 0)
// 		printf("Test case 6 passed!\n");
// 	else
// 		printf("Test case 6 failed!\n");
// }

// int	main(void)
// {
// 	test_ft_isalnum();
// 	return (0);
// }
