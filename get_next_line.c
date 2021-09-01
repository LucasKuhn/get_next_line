/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalexk-ku <lalex-ku@42sp.org.br>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 21:42:34 by lalexk-ku         #+#    #+#             */
/*   Updated: 2021/08/31 22:19:50 by lalexk-ku        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	buffer_contains_break(char *buffer);
static void	append_to_buffer(char **saved_buffer, int fd, char *read_buffer);
static char	*get_line_from_buffer(char **saved_buffer, int fd);

char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	char		read_buffer[BUFFER_SIZE + 1];
	static char	*saved_buffer[1024];

	while (!buffer_contains_break(saved_buffer[fd]))
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		read_buffer[bytes_read] = '\0';
		if (saved_buffer[fd])
			append_to_buffer(saved_buffer, fd, read_buffer);
		else
			saved_buffer[fd] = ft_strdup(read_buffer);
	}
	if (!saved_buffer[fd])
		return (NULL);
	return (get_line_from_buffer(saved_buffer, fd));
}

static void	append_to_buffer(char **saved_buffer, int fd, char *read_buffer)
{
	char		*temp;

	temp = ft_strjoin(saved_buffer[fd], read_buffer);
	free(saved_buffer[fd]);
	saved_buffer[fd] = temp;
}

static int	buffer_contains_break(char *buffer)
{
	if (!buffer)
		return (0);
	if (ft_strchr(buffer, '\n'))
		return (1);
	return (0);
}

static char	*get_line_from_buffer(char **saved_buffer, int fd)
{
	size_t	len;
	char	*line;
	char	*remaining_buffer;

	if (buffer_contains_break(saved_buffer[fd]))
	{
		len = 0;
		while (saved_buffer[fd][len] && saved_buffer[fd][len] != '\n')
			len++;
		line = malloc(sizeof(char) * ++len + 1);
		if (!line)
			return (NULL);
		ft_memcpy(line, saved_buffer[fd], len);
		line[len] = '\0';
		remaining_buffer = ft_strdup(saved_buffer[fd] + len);
	}
	else
	{
		line = ft_strdup(saved_buffer[fd]);
		remaining_buffer = NULL;
	}
	free(saved_buffer[fd]);
	saved_buffer[fd] = remaining_buffer;
	return (line);
}
