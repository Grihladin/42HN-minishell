/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:06:05 by mratke            #+#    #+#             */
/*   Updated: 2024/10/09 17:28:11 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *lhs, const char *rhs)
{
	size_t	i;

	i = 0;
	while (lhs[i] == rhs[i])
	{
		if (lhs[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return ((unsigned char)lhs[i] - (unsigned char)rhs[i]);
}

// void	test_ft_strcmp(void)
// {
// 	int	result;

// 	// Test case 1: Comparing two equal strings
// 	result = ft_strcmp("Hello", "Hello");
// 	printf("Test case 1: ");
// 	if (result == 0)
// 		printf("Passed! (result: %d)\n", result);
// 	else
// 		printf("Failed! (result: %d)\n", result);
// 	// Test case 2: Comparing two different strings
// 	result = ft_strcmp("Hello", "World");
// 	printf("Test case 2: ");
// 	if (result < 0)
// 		printf("Passed! (result: %d)\n", result);
// 	else
// 		printf("Failed! (result: %d)\n", result);
// 	// Test case 3: Comparing two different strings (reversed)
// 	result = ft_strcmp("World", "Hello");
// 	printf("Test case 3: ");
// 	if (result > 0)
// 		printf("Passed! (result: %d)\n", result);
// 	else
// 		printf("Failed! (result: %d)\n", result);
// 	// Test case 4: Comparing an empty string with a non-empty string
// 	result = ft_strcmp("", "Hello");
// 	printf("Test case 4: ");
// 	if (result < 0)
// 		printf("Passed! (result: %d)\n", result);
// 	else
// 		printf("Failed! (result: %d)\n", result);
// 	// Test case 5: Comparing a non-empty string with an empty string
// 	result = ft_strcmp("Hello", "");
// 	printf("Test case 5: ");
// 	if (result > 0)
// 		printf("Passed! (result: %d)\n", result);
// 	else
// 		printf("Failed! (result: %d)\n", result);
// 	// Test case 6: Comparing two empty strings
// 	result = ft_strcmp("", "");
// 	printf("Test case 6: ");
// 	if (result == 0)
// 		printf("Passed! (result: %d)\n", result);
// 	else
// 		printf("Failed! (result: %d)\n", result);
// }

// int	main(void)
// {
// 	test_ft_strcmp();
// 	return (0);
// }
