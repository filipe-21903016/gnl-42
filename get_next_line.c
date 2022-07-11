/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzarco-l <fzarco-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 01:54:26 by fzarco-l          #+#    #+#             */
/*   Updated: 2022/07/11 23:24:14 by fzarco-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

void	append_buffer(char **lines, char *buffer, int b_len)
{	
	int	lines_len;

	if (!*lines)
	{
		*lines = malloc(sizeof(char) * (b_len + 1));
		if (!*lines)
			return ;
		ft_strncpy(*lines, buffer, b_len);
		(*lines)[b_len] = '\0';
	}
	else
	{
		lines_len = ft_strlen(*lines);
		ft_realloc(lines, b_len + 1);
		ft_strncpy(*lines + lines_len, buffer, b_len);
		(*lines)[lines_len + b_len] = '\0';
	}
}

char	*get_line(char **lines, int read_bytes)
{
	char	*temp;
	char	*new_lines;
	int		i;
	int		new_length;
	int		lines_len;

	if (*lines == NULL)
		return (NULL);
	lines_len = ft_strlen(*lines);
	if (read_bytes == 0)
	{
		temp = malloc(sizeof(char) * (lines_len + 1));
		if (!temp)
			return (NULL);
		/* puts("cpyin"); */
		ft_strncpy(temp, *lines, lines_len);
		/* puts("cpyout"); */
		temp[lines_len] = '\0';
		free(*lines);
	}
	else
	{
		i = ft_strchr(*lines, '\n');
		temp = malloc(sizeof(char) * (i + 2));
		if (!temp)
			return (NULL);
		ft_strncpy(temp, *lines, i + 1);
		temp[i + 1] = '\0';
		new_length = lines_len - i - 1;
		new_lines = malloc(sizeof(char) * new_length);
		if (!new_lines)
			return (NULL);
		ft_strncpy(new_lines, *lines + i + 1, new_length);
		free(*lines);
		*lines = new_lines;
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*lines;
	char		*buffer;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	read_bytes = 1;
	while (read_bytes != 0 && ft_strchr(lines,'\n') == -1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes > 0)
		{
			buffer[read_bytes] = '\0';
			append_buffer(&lines, buffer, read_bytes);
		}
	}
	free(buffer);
	if(lines != NULL && ft_strlen(lines) < 1 && read_bytes == 0)
		return (NULL);
	return get_line(&lines, read_bytes);
}
int main(int ac, char **av) {
    int fd = open("test.txt", O_RDONLY);
	(void)ac;
	av++;
	printf("%s",get_next_line(fd));
	if (get_next_line(fd) == NULL)
		puts("my nigga");
   close(fd);
}
