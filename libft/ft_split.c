/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:51:43 by mratke            #+#    #+#             */
/*   Updated: 2024/10/13 17:41:58 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	result_size_calculator(char const *s, char c)
{
	size_t	array_size;
	size_t	i;
	int		word_flag;

	word_flag = 0;
	array_size = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && word_flag == 0)
		{
			word_flag = 1;
			array_size++;
		}
		else if (s[i] == c)
		{
			word_flag = 0;
		}
		i++;
	}
	return (array_size);
}

static char	*word_cpy(const char *src, size_t start, size_t end)
{
	size_t	i;
	char	*result;
	size_t	length;

	length = end - start;
	i = 0;
	result = malloc((length + 1) * sizeof(char));
	if (result == NULL)
	{
		return (NULL);
	}
	while (i < length)
	{
		result[i] = src[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static int	get_word_end(const char *s, int i, char c)
{
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static void	free_result(char **result, size_t j)
{
	while (j > 0)
	{
		j--;
		free(result[j]);
	}
	free(result);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**result;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	result = malloc((result_size_calculator(s, c) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		start = i;
		i = get_word_end(s, i, c);
		if (i != start)
		{
			result[j] = word_cpy(s, start, i);
			if (result[j] == NULL)
				return (free_result(result, j), NULL);
			j++;
		}
	}
	return (result[j] = NULL, result);
}

// int	main(void)
// {
// 	char	**result;
// 	int		i;
// 	int		j;
// 	char	s[100] = "                  olol";

// 	result = ft_split(s, ' ');
// 	i = 0;
// 	j = 0;
// 	while (result[i] != NULL)
// 	{
// 		printf(" {");
// 		while (result[i][j] != '\0')
// 		{
// 			printf("%c", result[i][j]);
// 			j++;
// 		}
// 		printf("}");
// 		i++;
// 		j = 0;
// 	}
// }
