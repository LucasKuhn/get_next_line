#include "get_next_line.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
	printf("BUFFER_SIZE=%d\n\n", BUFFER_SIZE);

	int fd_0 = open("empty", O_RDONLY);
	printf("GNL->(%s)", get_next_line(fd_0));
	printf("GNL->(%s)", get_next_line(fd_0));
	close(fd_0);

	int fd_1 = open("numbers", O_RDONLY);
	printf("GNL: %s", get_next_line(fd_1));
	printf("GNL: %s", get_next_line(fd_1));
	close(fd_1);

	int fd_2 = open("song", O_RDONLY);
	printf("GNL: %s", get_next_line(fd_2));
	printf("GNL: %s", get_next_line(fd_2));
	close(fd_2);
}
