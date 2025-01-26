/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:39:03 by mratke            #+#    #+#             */
/*   Updated: 2024/10/10 12:31:22 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

// void	test_ft_strlen(void)
// {
// 	int	result;

// 	// Test case 1: Empty string
// 	result = ft_strlen("");
// 	if (result == 0)
// 		printf("Test case 1 passed!\n");
// 	else
// 		printf("Test case 1 failed!\n");
// 	// Test case 2: String with length 5
// 	result = ft_strlen("Hello");
// 	if (result == 5)
// 		printf("Test case 2 passed!\n");
// 	else
// 		printf("Test case 2 failed!\n");
// 	// Test case 3: String with spaces
// 	result = ft_strlen("Hello, World!");
// 	if (result == 13)
// 		printf("Test case 3 passed!\n");
// 	else
// 		printf("Test case 3 failed!\n");
// 	// Test case 4: String with special characters
// 	result = ft_strlen("\t\n@!");
// 	if (result == 4)
// 		printf("Test case 4 passed!\n");
// 	else
// 		printf("Test case 4 failed!\n");
// }

// int	main(void)
// {
// 	test_ft_strlen();
// 	return (0);
// }
