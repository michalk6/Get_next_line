/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikurek <mikurek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:17:13 by mikurek           #+#    #+#             */
/*   Updated: 2024/12/18 21:49:19 by mikurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
	#include <stdio.h>

int	ft_check_for_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_read_file(int fd, char *stream)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = BUFFER_SIZE;
	while (!ft_check_for_line(stream))
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[BUFFER_SIZE] = 0;
		stream = ft_strjoin(stream, buffer);
		if (bytes_read < BUFFER_SIZE)
			break ;
	}
	return (stream);
}

char	*ft_cut_stream(char *stream)
{
	int		i;

	i = 0;
	while (stream[i] && stream[i] != '\n')
		i++;
	return (ft_substr(stream, i + 1, ft_strlen(stream) - i));
}

char	*ft_read_line(char *stream)
{
	char	*line;
	int		i;

	i = 0;
	while (stream[i] && stream[i] != '\n')
		i++;
	line = ft_substr(stream, 0, i + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stream;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stream == NULL)
		stream = "";
	if (!ft_check_for_line(stream))
		stream = ft_read_file(fd, stream);
	line = ft_read_line(stream);
	if (*stream == 0)
	{
		free(stream);
		return (NULL);
	}
	stream = ft_cut_stream(stream);
	return (line);
}
