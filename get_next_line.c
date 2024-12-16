/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikurek <mikurek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:17:13 by mikurek           #+#    #+#             */
/*   Updated: 2024/12/16 23:31:15 by mikurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
	#include <stdio.h>

char	*ft_get_line(char **stream)
{
	char	*line;
	int		i;

	i = 0;
	while (*stream[i] != '\n')
	{
		printf("robię stream %d \n", i);
		if (!(*stream[i])){
		printf("zwracam null \n");
			return (NULL);}
		i++;
	}
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	line = ft_substr(*stream, 0, i);
		printf("in ft_get_line stream = %s", stream);
	stream = &stream[i];
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stream;
	char		*buffer;
	char		*line;
		printf("declarations in get line\n");
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stream)
		stream = "";
		printf("stream = %s\n", stream);
	line = 0;
		printf("line = %s\n", line);

	while (!line)
	{
			printf("in while\n");
		line = ft_get_line(&stream);
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (NULL);
		read(fd, buffer, BUFFER_SIZE);
		stream = ft_strjoin(stream, buffer);
	}
	return (line);
}
