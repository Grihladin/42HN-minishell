/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:04:43 by mratke            #+#    #+#             */
/*   Updated: 2024/10/13 17:48:18 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*result;

	if (s == NULL || f == NULL)
		return (NULL);
	result = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// char	ft_special_toupper(unsigned int i, char c)
// {
// 	char	ch;

// 	ch = c;
// 	if (ch >= 'a' && ch <= 'z')
// 	{
// 		return (ch - 32);
// 	}
// 	return (ch);
// }

// int	main(void)
// {
// 	int		i;
// 	char	s[10] = "qwer";
// 	char	*str;

// 	i = 0;
// 	str = ft_strmapi(s, ft_special_toupper(i, s[i]));
// 	while (str[i] != '\0')
// 	{
// 		printf("%c", str[i]);
// 		i++;
// 	}
// }
