/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:49:35 by mratke            #+#    #+#             */
/*   Updated: 2024/10/08 11:57:27 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int ch)
{
	if (ch >= 32 && ch <= 126)
	{
		return (1);
	}
	return (0);
}

// void	test_ft_isprint(void)
// {
// 	int	result;

// 	// Test case 1: Printable character (space)
// 	result = ft_isprint(32);
// 	if (result == 1)
// 		printf("Test case 1 passed!\n");
// 	else
// 		printf("Test case 1 failed!\n");

// 	// Test case 2: Printable character ('A')
// 	result = ft_isprint('A');
// 	if (result == 1)
// 		printf("Test case 2 passed!\n");
// 	else
// 		printf("Test case 2 failed!\n");

// 	// Test case 3: Non-printable character (ASCII 10)
// 	result = ft_isprint(10);  // Line feed (non-printable)
// 	if (result == 0)
// 		printf("Test case 3 passed!\n");
// 	else
// 		printf("Test case 3 failed!\n");

// 	// Test case 4: Non-printable character (ASCII 127)
// 	result = ft_isprint(127);  // DEL (non-printable)
// 	if (result == 0)
// 		printf("Test case 4 passed!\n");
// 	else
// 		printf("Test case 4 failed!\n");

// 	// Test case 5: Printable character ('~')
// 	result = ft_isprint(126);
// 	if (result == 1)
// 		printf("Test case 5 passed!\n");
// 	else
// 		printf("Test case 5 failed!\n");
// }

// int	main(void)
// {
// 	test_ft_isprint();
// 	return (0);
// }
