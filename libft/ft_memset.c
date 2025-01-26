/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:27:11 by mratke            #+#    #+#             */
/*   Updated: 2024/10/09 18:20:17 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int ch, size_t count)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)dest;
	i = 0;
	while (i < count)
	{
		ptr[i] = (unsigned char)ch;
		i++;
	}
	return (dest);
}

// void	test_ft_memset(void)
// {
// 	size_t	i;
// 	char	*result;
// 	char	original[5] = {'X', 'Y', 'Z', 'W', 'V'};

// 	char buffer[50]; // Buffer to test ft_memset
// 	// Test case 1: Fill the buffer with 'A'
// 	ft_memset(buffer, 'A', 10);
// 	printf("Test case 1: ");
// 	for (i = 0; i < 10; i++)
// 	{
// 		if (buffer[i] != 'A')
// 			break ;
// 	}
// 	if (i == 10)
// 		printf("Passed!\n");
// 	else
// 		printf("Failed! (buffer[0] to buffer[9] != 'A')\n");
// 	// Test case 2: Fill the remaining buffer with 'B'
// 	ft_memset(buffer + 10, 'B', 10);
// 	printf("Test case 2: ");
// 	for (i = 10; i < 20; i++)
// 	{
// 		if (buffer[i] != 'B')
// 			break ;
// 	}
// 	if (i == 20)
// 		printf("Passed!\n");
// 	else
// 		printf("Failed! (buffer[10] to buffer[19] != 'B')\n");
// 	// Test case 3: Fill with zero (null characters)
// 	ft_memset(buffer, '\0', 10);
// 	printf("Test case 3: ");
// 	for (i = 0; i < 10; i++)
// 	{
// 		if (buffer[i] != '\0')
// 			break ;
// 	}
// 	if (i == 10)
// 		printf("Passed!\n");
// 	else
// 		printf("Failed! (buffer[0] to buffer[9] != null terminator)\n");
// 	// Test case 4: Test the return value of ft_memset
// 	result = ft_memset(buffer, 'C', 5);
// 	printf("Test case 4: ");
// 	if (result == buffer)
// 		printf("Passed! (Returned pointer matches original buffer)\n");
// 	else
// 		printf("Failed! (Returned pointer does not match original buffer)\n");
// 	// Test case 5: Check length zero (no modification)
// 	ft_memset(original, 'A', 0);
// 	printf("Test case 5: ");
// 	if (original[0] == 'X' && original[1] == 'Y' && original[2] == 'Z'
// 		&& original[3] == 'W' && original[4] == 'V')
// 	{
// 		printf("Passed! (Buffer unchanged)\n");
// 	}
// 	else
// 	{
// 		printf("Failed! (Buffer modified)\n");
// 	}
// }

// int	main(void)
// {
// 	test_ft_memset();
// 	return (0);
// }
