#include "get_next_line.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
	printf("BUFFER_SIZE=%d\n", BUFFER_SIZE);


	int fd_1 = open("numbers", O_RDONLY);
	int fd_2 = open("numbers", O_RDONLY);

	printf("GNL->%s \n", get_next_line(fd_1));
	printf("GNL->%s \n", get_next_line(fd_1));
	// printf("GNL: %s \n", get_next_line(fd_2));
	// printf("GNL: %s \n", get_next_line(fd_1));
	// printf("FD: %d \n", fd_1);

	// printf("GNL: %s \n", get_next_line(fd_2));
	// printf("GNL: %s \n", get_next_line(fd_1));
	// printf("FD: %d \n", fd_1);

	// printf("GNL: %s \n", get_next_line(fd_2));
	// printf("GNL: %s \n", get_next_line(fd_1));
	// printf("GNL: %s \n", get_next_line(fd_2));
	// printf("GNL: %s \n", get_next_line(fd_1));
	// printf("GNL: %s \n", get_next_line(fd_2));
	// printf("GNL: %s \n", get_next_line(fd_1));
	// printf("GNL: %s \n", get_next_line(fd_2));


	close(fd_1);
	close(fd_2);
}

