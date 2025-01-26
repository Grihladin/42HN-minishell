/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:19:00 by mratke            #+#    #+#             */
/*   Updated: 2024/10/13 18:41:43 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_len_calculator(const int n)
{
	int	i;
	int	n_cpy;

	i = 0;
	n_cpy = n;
	if (n_cpy <= 0)
	{
		n_cpy = -n_cpy;
		i++;
	}
	while (n_cpy > 0)
	{
		n_cpy = n_cpy / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	int		buffer;
	char	*result;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = (n_len_calculator(n) + 1);
	result = malloc(i * sizeof(char));
	if (result == NULL)
		return (NULL);
	if (n == 0)
		return (result[0] = '0', result[1] = '\0', result);
	if (n < 0)
	{
		n = -n;
		result[0] = '-';
	}
	result[--i] = '\0';
	while (n > 0)
	{
		buffer = n % 10;
		result[--i] = buffer + '0';
		n /= 10;
	}
	return (result);
}

// int	main(void)
// {
// 	int		i;
// 	int		n;
// 	char	*s;

// 	i = 0;
// 	n = 10000;
// 	s = ft_itoa(n);
// 	while (s[i] != '\0')
// 	{
// 		printf("%c", s[i]);
// 		i++;
// 	}
// 	printf("\nsize = %i", n_len_calculator(n));
// }
