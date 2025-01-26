/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:01:53 by mratke            #+#    #+#             */
/*   Updated: 2024/10/11 13:31:02 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, s1_len + s2_len + 1);
	ft_strlcat(result, s2, s1_len + s2_len + 1);
	return (result);
}

// int	main(void)
// {
// 	int		i;
// 	char	s1[50] = "Michael ";
// 	char	s2[50] = "Ratke";
// 	char	*joincheck;

// 	i = 0;
// 	joincheck = ft_strjoin(s1, s2);
// 	while (joincheck[i] != '\0')
// 	{
// 		printf("%c", joincheck[i]);
// 		i++;
// 	}
// }
