/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:07:38 by mratke            #+#    #+#             */
/*   Updated: 2024/10/12 15:09:40 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	if (s_len - start < len)
		len = s_len - start;
	result = malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	j = (size_t)start;
	while (i < len)
	{
		result[i] = s[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}

// int	main(void)
// {
// 	char	*str;
// 	size_t	size;
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	str = "01234";
// 	size = 10;
// 	ret = ft_substr("", 1, 1);
// 	i = 0;
// 	while (ret[i] != '\0')
// 	{
// 		printf("%c", ret[i]);
// 		i++;
// 	}
// }
