#include "get_next_line.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
	printf("BUFFER_SIZE=%d\n", BUFFER_SIZE);
	static char buffer[BUFFER_SIZE];

	size_t nbytes;
	nbytes = sizeof(buffer);

	int fd_1 = open("whatever", O_RDONLY);

	ssize_t bytes_read;
	
	bytes_read = read(fd_1, buffer, nbytes);
	printf("Bytes read: %zd\n", bytes_read);
	printf("buffer: %s\n", buffer);


	close(fd_1);
}

