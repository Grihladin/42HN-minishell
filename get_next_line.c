/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:34:23 by mratke            #+#    #+#             */
/*   Updated: 2025/02/09 23:04:09 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_and_merge(int fd, char *current_line)
{
	char	*tmp;
	char	*chars_readed;
	int		bytes_readed;

	chars_readed = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (chars_readed == NULL)
		return (free(current_line), NULL);
	chars_readed[0] = '\0';
	while (is_in_str(chars_readed, '\n') < 0)
	{
		bytes_readed = read(fd, chars_readed, BUFFER_SIZE);
		if (bytes_readed == -1)
			return (free(chars_readed), free(current_line), NULL);
		if (bytes_readed == 0)
			break ;
		chars_readed[bytes_readed] = '\0';
		tmp = ft_str_merge(current_line, chars_readed);
		if (tmp == NULL)
			return (free(chars_readed), free(current_line), NULL);
		free(current_line);
		current_line = tmp;
	}
	free(chars_readed);
	return (current_line);
}

char	*line_validator(char *s)
{
	int		i;
	char	*validated_line;
	int		j;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			break ;
		i++;
	}
	validated_line = malloc((i + 2) * sizeof(char));
	if (validated_line == NULL)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		validated_line[j] = s[j];
		j++;
	}
	validated_line[j] = '\0';
	return (validated_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer == NULL)
	{
		buffer = malloc(sizeof(char));
		if (buffer == NULL)
			return (NULL);
		buffer[0] = '\0';
	}
	buffer = read_and_merge(fd, buffer);
	if (buffer == NULL || buffer[0] == '\0')
		return (free(buffer), buffer = NULL, NULL);
	line = line_validator(buffer);
	if (line == NULL)
		return (free(buffer), NULL);
	tmp = ft_strdup(buffer + ft_strlen(line));
	if (tmp == NULL)
		return (free(line), free(buffer), NULL);
	free(buffer);
	buffer = tmp;
	return (line);
}
// int	main(void)
// {
// 	int		fd;
// 	char	*st;
// 	int		i;

// 	fd = open("test.txt", O_RDONLY);
// 	i = 3;
// 	while (i > 0)
// 	{
// 		st = get_next_line(fd);
// 		printf("%s\n", st);
// 		i--;
// 	}
// }
