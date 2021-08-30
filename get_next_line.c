#include "get_next_line.h"

#include <stdio.h>

char *get_line_from_static_buffer(char **saved_buffer, int fd)
{
	size_t	len;
	char	*line;
	char	*temp;

	if (!saved_buffer[fd])
		return (NULL);
	len = 0;
	while (saved_buffer[fd][len] && saved_buffer[fd][len] != '\n')
		len++;
	line = malloc(sizeof(char) * ++len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, saved_buffer[fd], len);
	line[len] = '\0';
	if (*(saved_buffer[fd] + (len - 1)) == '\0')
		saved_buffer[fd] = 0;
	else
	{
		temp = ft_strdup(saved_buffer[fd] + len);
		free(saved_buffer[fd]);
		saved_buffer[fd] = temp;
	}
	return (line);
}

// Allowed: read, malloc, free
// Return: Read line: correct behavior
// NULL: nothing else to read or an error occurred
char *get_next_line(int fd)
{
	ssize_t bytes_read;
	char read_buffer[BUFFER_SIZE + 1];
	static char *saved_buffer[1024];
	char		*temp;

	if ( saved_buffer[fd] && ft_strchr(saved_buffer[fd], '\n') )
		return (get_line_from_static_buffer(saved_buffer, fd));
	while ( (bytes_read = read(fd, read_buffer, BUFFER_SIZE)) > 0 )
	{
		read_buffer[bytes_read] = 0;
		if (saved_buffer[fd])
		{
			temp = ft_strjoin(saved_buffer[fd], read_buffer);
			free(saved_buffer[fd]);
			saved_buffer[fd] = temp;
		}
		else
			saved_buffer[fd] = ft_strdup(read_buffer);
		if ( ft_strchr(saved_buffer[fd], '\n') )
			break;
	}
	return (get_line_from_static_buffer(saved_buffer, fd));
}


#include <stdio.h>
int main()
{
	printf("BUFFER_SIZE=%d\n\n", BUFFER_SIZE);

	int fd_1 = open("numbers", O_RDONLY);

	printf("GNL: %s", get_next_line(fd_1));
	printf("GNL: %s", get_next_line(fd_1));
	printf("GNL: %s", get_next_line(fd_1));
	printf("GNL: %s", get_next_line(fd_1));
	printf("GNL: %s", get_next_line(fd_1));
	printf("GNL: %s", get_next_line(fd_1));

	int fd_2 = open("song", O_RDONLY);
	printf("\n--File 2--\n");
	printf("GNL: %s", get_next_line(fd_2));
	printf("GNL: %s", get_next_line(fd_2));

	close(fd_1);
	close(fd_2);
}

