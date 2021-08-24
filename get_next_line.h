#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

#include <unistd.h> // Read
#include <stdlib.h> // Malloc, Free
#include <fcntl.h> // O_RDONLY

char *get_next_line(int fd);

# endif