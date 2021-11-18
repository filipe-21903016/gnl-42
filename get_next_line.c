# include "get_next_line.h"

#include <limits.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX][BUFFER_SIZE];
	//char		*line;
	//int			read_bytes;
	//int			index;

	if (fd < 0)
		return (NULL);
	read(fd, buffer[fd], BUFFER_SIZE);
	printf("%s\n", buffer[fd]);
	return (NULL);
}

#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	int fd = open("get_next_line.h", O_RDONLY);
	get_next_line(fd);
}
