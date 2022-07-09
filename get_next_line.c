# include "get_next_line.h"
# include <limits.h>
# include <string.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>

int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (*str++)
		count++;
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_strncpy(char *restrict dest, const char *restrict src, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = dest;
	while (src[i] != '\0' && i < n)
		*ptr++ = src[i++];
	while (i++ < n)
		*ptr++ = '\0';
	return (dest);
}

void	ft_realloc(char **buf, int size)
{
	char	*new;
	int		buf_len;

	buf_len = ft_strlen(*buf);
	new = malloc(sizeof(char) * (buf_len + 1 + size));
	if (!new)
		return ;
	ft_strncpy(new, *buf, buf_len);
	printf("%s\n\n%s", new, *buf);
	free(buf);
	buf = &new;
}

char	*extract_line(char **buffer)
{
	int		i;
	char	*line;
	char	*new_buffer;

	i = 0;
	while (*buffer[i] != '\0')
	{
		if (*buffer[i] == '\n') 
		{
			//sacar linha
			line = malloc(sizeof(char) * i + 1);
			ft_strncpy(line, *buffer, i + 1);
			printf("%s\n", line);
			//criar memoria com novo buffer avancado i
			new_buffer = malloc(sizeof(char) * (ft_strlen(*buffer - i) + 1));
			ft_strncpy(new_buffer, *(buffer + i + 1), ft_strlen(*buffer - i));
			//libertar buffer antigo
			free(*buffer);
			//enderecar o ptr a nova memoria
			buffer = &new_buffer;
			return (line);
		}
		i++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;
	int			read_bytes;

	if (fd < 0)
		return (NULL);
	read_bytes = -1;
	if (buffer[fd] == NULL)
	{
		buffer[fd] = malloc(sizeof(char) * 1);
		buffer[fd][0] = '\0';
	}
	while (ft_strchr(buffer[fd], '\n') == NULL && read_bytes != 0)
	{
		ft_realloc(&buffer[fd], BUFFER_SIZE);	
		if (!buffer[fd])
			return (NULL);
		read_bytes = read(fd, buffer[fd], BUFFER_SIZE);
		printf("%d", read_bytes);
	}
	line = extract_line(&buffer[fd]);
	if (line)
		return (line);
	return (NULL);
}


int main(int ac, char **av)
{
	char *line;
	int fd = open("get_next_line.h", O_RDONLY);

	(void)ac;
	av++;
	while ((line = get_next_line(fd))!= NULL)
		printf("%s\n", line);
	close(fd);
}
