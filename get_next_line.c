/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikurek <mikurek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:17:13 by mikurek           #+#    #+#             */
/*   Updated: 2024/12/18 22:39:43 by mikurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	char	*temp;

	bytes_read = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_check_for_line(stream) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = 0;
		temp = ft_strjoin(stream, buffer);
		stream = temp;
	}
	free(buffer);
	return (stream);
}

char	*ft_cut_stream(char *stream)
{
	char	*cut;
	int		i;

	i = 0;
	while (stream[i] && stream[i] != '\n')
		i++;
	cut = ft_substr(stream, i + 1, ft_strlen(stream) - i);
	free(stream);
	return (cut);
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
