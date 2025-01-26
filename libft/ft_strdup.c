/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:21:17 by mratke            #+#    #+#             */
/*   Updated: 2024/10/10 18:22:17 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		src_len;
	char	*dup;
	int		i;

	src_len = ft_strlen(src);
	dup = malloc((src_len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// int	main(void)
// {
// 	char	*s;
// 	char	*sdup;
// 	int		i;

// 	i = 0;
// 	s = "fashdfahs";
// 	sdup = ft_strdup(s);
// 	while (sdup[i] != '\0')
// 	{
// 		printf("%c", sdup[i]);
// 		i++;
// 	}
// }
