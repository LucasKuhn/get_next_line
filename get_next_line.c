#include "get_next_line.h"

#include <stdio.h>

char *get_next_line(int fd)
{
	ssize_t bytes_read;
	char tmp[1];
	int i;

	static char buffer[BUFFER_SIZE + 1];

	// Clears the buffer (bzero) 
	i = 0;
	while (i < BUFFER_SIZE)
	{
		buffer[i] = 0;
		i++;
	}

	i = 0;
	while ( i < BUFFER_SIZE )
	{
		bytes_read = read(fd, tmp, 1);
		// Can't read (EOF) of it reached a new line
		if (bytes_read != 1 || *tmp == '\n') 
			break; // Goes outside while
		buffer[i++] = *tmp;
	}
	// while (bytes_read == 1 && *tmp != '\n')
	// {
	// 	bytes_read = read(fd, tmp, 1);
	// }
	return (buffer);
}