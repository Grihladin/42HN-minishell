/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:37:08 by mratke            #+#    #+#             */
/*   Updated: 2024/10/08 11:48:36 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}

// void	test_ft_isascii(void)
// {
// 	int	result;

// 	// Test case 1: Check if 0 is ASCII (lower boundary)
// 	result = ft_isascii(0);
// 	if (result == 1)
// 		printf("Test case 1 passed!\n");
// 	else
// 		printf("Test case 1 failed!\n");

// 	// Test case 2: Check if 127 is ASCII (upper boundary)
// 	result = ft_isascii(127);
// 	if (result == 1)
// 		printf("Test case 2 passed!\n");
// 	else
// 		printf("Test case 2 failed!\n");

// 	// Test case 3: Check if 65 ('A') is ASCII (valid character)
// 	result = ft_isascii(65);
// 	if (result == 1)
// 		printf("Test case 3 passed!\n");
// 	else
// 		printf("Test case 3 failed!\n");

// 	// Test case 4: Check if -1 is not ASCII
// 	result = ft_isascii(-1);
// 	if (result == 0)
// 		printf("Test case 4 passed!\n");
// 	else
// 		printf("Test case 4 failed!\n");

// 	// Test case 5: Check if 128 is not ASCII (out of range)
// 	result = ft_isascii(128);
// 	if (result == 0)
// 		printf("Test case 5 passed!\n");
// 	else
// 		printf("Test case 5 failed!\n");
// }

// int	main(void)
// {
// 	test_ft_isascii();
// 	return (0);
// }
