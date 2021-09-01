#include "get_next_line.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
	printf("BUFFER_SIZE=%d", BUFFER_SIZE);

	puts("\n\n --- Empty ---");
	int fd_0 = open("empty", O_RDONLY);
	printf("->%s", get_next_line(fd_0));
	printf("->%s", get_next_line(fd_0));
	printf("->%s", get_next_line(fd_0));


	puts("\n\n --- Numbers ---");
	int fd_1 = open("numbers", O_RDONLY);
	printf("->%s", get_next_line(fd_1));
	printf("->%s", get_next_line(fd_1));
	printf("->%s", get_next_line(fd_1));

	puts("\n\n --- Song ---");
	int fd_2 = open("song", O_RDONLY);
	printf("->%s", get_next_line(fd_2));
	printf("->%s", get_next_line(fd_2));
	printf("->%s", get_next_line(fd_2));
	printf("->%s", get_next_line(fd_2));

	close(fd_0);
	close(fd_1);
	close(fd_2);
}
