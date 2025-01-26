/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:33:25 by mratke            #+#    #+#             */
/*   Updated: 2024/10/11 16:47:06 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	j;
	char	*result;

	start = 0;
	end = ft_strlen(s1);
	j = 0;
	while (end > 0 && is_in_set(s1[end - 1], set) == 1)
		end--;
	while (s1[start] != '\0' && is_in_set(s1[start], set) == 1)
		start++;
	if (start >= end)
		return (ft_strdup(""));
	result = malloc((end - start + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (start < end)
	{
		result[j] = s1[start];
		start++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

// int	main(void)
// {
// 	char	*trimmed;
// 	int		i;
// 	char	*s;

// 	s = "qqq";
// 	trimmed = ft_strtrim(s, "q");
// 	i = 0;
// 	while (trimmed[i] != '\0')
// 	{
// 		printf("%c", trimmed[i]);
// 		i++;
// 	}
// 	printf("\n len = %i", ft_strlen(s));
// }
