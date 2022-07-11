/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzarco-l <fzarco-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 01:54:26 by fzarco-l          #+#    #+#             */
/*   Updated: 2022/07/11 19:25:35 by fzarco-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

void	append_buffer(t_lines **lines, char *buffer, int b_size)
{	
	if (!*lines)
	{
		*lines = malloc(sizeof(t_lines));
		if (!*lines)
			return ;
		(*lines)->lines = malloc(sizeof(char) * b_size);
		if (!(*lines)->lines)
			return ;
		ft_strncpy((*lines)->lines, buffer, b_size);
		(*lines)->length = b_size;
	}
	else
	{
		ft_lines_realloc(lines, b_size);
		ft_strncpy((*lines)->lines + (*lines)->length, buffer, b_size);
		(*lines)->length = (*lines)->length + b_size;
	}
}

char	*get_line(t_lines **lines, int read_bytes)
{
	char	*temp;
	char	*new_lines;
	int		i;
	int		new_length;

	if (!*lines)
		return (NULL);
	printf("lines:%s", (*lines)->lines);
	puts("passou o nul check");
	if (read_bytes == 0)
	{
		temp = malloc(sizeof(char) * ((*lines)->length + 1));
		if (!temp)
			return (NULL);
		ft_strncpy(temp, (*lines)->lines, (*lines)->length);
		new_lines = NULL;
		new_length = 0;
	}
	else {
		i = ft_strchr((*lines)->lines,(*lines)->length, '\n');
		temp = malloc(sizeof(char) * i + 2);
		if (!temp)
			return (NULL);
		ft_strncpy(temp, (*lines)->lines, i + 1);
		temp[i + 1] = '\0';
		new_length = (*lines)->length - i - 1;
		new_lines = malloc(sizeof(char) * new_length);
		if (!new_lines)
			return (NULL);
		ft_strncpy(new_lines, (*lines)->lines + i + 1, new_length);
	}
	free((*lines)->lines);
	(*lines)->lines = new_lines;
	(*lines)->length = new_length;
	return (temp);
}

char	*get_next_line(int fd)
{
	static t_lines	*lines;
	char			*line;
	char			*buffer;
	int				read_bytes;

	if (fd < 0 || fcntl(fd, F_GETFD) < 0)
		return (NULL);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	read_bytes = -1;
	while (read_bytes != 0 && ft_strchr(buffer, ft_strlen(buffer), '\n') == -1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes > 0)
		{
			buffer[read_bytes] = '\0';
			append_buffer(&lines, buffer, read_bytes);
		}
	}
	free(buffer);
	line = get_line(&lines, read_bytes);
	if(line == NULL)
		puts("yup its null");
	if (lines->lines == NULL)
	{
		free(lines);
		lines = NULL;
	}
	return line;
}
#include <stdio.h>
int main(int ac, char **av) {
    int fd = open("test.txt", O_RDONLY);
    char *line;
	(void)ac;
	av++;
    /* while ((line = get_next_line(fd)) != NULL) */
    /*     printf("%s", line); */
	get_next_line(fd);
	if(get_next_line(fd) == NULL)
		puts("yup its null");
    close(fd);
}
