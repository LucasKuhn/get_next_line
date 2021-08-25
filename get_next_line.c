#include "get_next_line.h"

#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		str_size;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	str_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(sizeof(char) * str_size);
	if (!str)
		return (NULL);
	i = 0;
	while (*s1)
	{
		str[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		str[i] = *s2;
		s2++;
		i++;
	}
	str[i] = '\0';
	return (&str[0]);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (n)
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i++;
		n--;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;

	len = ft_strlen((char *)s1) + 1;
	dup = malloc(sizeof(*s1) * len);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s1, len);
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == c)
		return ((char *)s + i);
	return (0);
}

char *get_line(char **saved_buffer, int fd)
{
	size_t	len;
	char	*line;
	char	*str;
	char	*remaining_buffer;

	str = saved_buffer[fd];	
	len = 0;
	printf("Str on Get_Line: %s \n", str);
	while (str[len] && str[len] != '\n')
		len++;
	line = malloc(sizeof(*str) * ++len);
	if (!line)
		return (NULL);
	ft_memcpy(line, str, len);
	remaining_buffer = ft_strdup(str + len);
	// free(saved_buffer[fd]);
	saved_buffer[fd] = remaining_buffer;
	saved_buffer[fd] = (str + len);
	printf("New saved buffer->(%s)\n", saved_buffer[fd]);
	printf("Line->(%s)\n", line);
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
	char *tmp;
	char *joined_str;

	// if ( ft_strchr(saved_buffer[fd], '\n') )
		// return (get_line(saved_buffer, fd));
	printf("Buffer before read -> %s\n", saved_buffer[fd]);
	// While read can read something
	while ( (bytes_read = read(fd, read_buffer, BUFFER_SIZE)) > 0 )
	{
		printf("Just read %zd bytes -> %s \n", bytes_read, read_buffer);
		if (saved_buffer[fd])
		{
			printf("%p | Saved bufffer->(%s)\n", saved_buffer[fd], saved_buffer[fd]);
			tmp = saved_buffer[fd];
			printf("%p | tmp->(%s)\n", tmp, tmp);
			joined_str = ft_strjoin(saved_buffer[fd], read_buffer);
			printf("%p | Joined STR->(%s)\n", joined_str, joined_str);
			saved_buffer[fd] = joined_str;
			printf("%p | Saved bufffer->(%s)\n", saved_buffer[fd], saved_buffer[fd]);
			printf("%p | tmp->(%s)\n", tmp, tmp);
		}
		else
		{
			printf("Buffer start\n");
			saved_buffer[fd] = ft_strdup(read_buffer);
		}
		printf("Buffer now -> %s\n", saved_buffer[fd]);
		if ( ft_strchr(saved_buffer[fd], '\n') )
		{
			printf("Buffer contains break!\n");
			break;
		}
	}
	char *str = get_line(saved_buffer, fd);
	return (str);
}


int main()
{
	printf("BUFFER_SIZE=%d\n", BUFFER_SIZE);


	int fd_1 = open("numbers", O_RDONLY);

	printf("GNL->%s \n", get_next_line(fd_1));
	printf("GNL->%s \n", get_next_line(fd_1));
	close(fd_1);
}

