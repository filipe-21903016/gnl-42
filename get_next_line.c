/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzarco-l <fzarco-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 01:54:26 by fzarco-l          #+#    #+#             */
/*   Updated: 2022/07/12 15:10:27 by fzarco-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	append_buffer(char **lines, char *buffer)
{	
	char	*temp_lines;
	if (!*lines)
		*lines = ft_strdup("");
	temp_lines = ft_strjoin(*lines, buffer);
	free(*lines);
	*lines = temp_lines;
}

char	*get_line(char **lines)
{
	char	*temp;
	char	*new_lines;
	int		has_nline;

	if (*lines == NULL)
		return (NULL);
	has_nline = ft_strchr(*lines, '\n');
	if (has_nline >= 0)
	{
		temp = ft_substr(*lines, 0, has_nline + 1);	
		new_lines = ft_substr(*lines, has_nline + 1, ft_strlen(*lines));
		free(*lines);
		*lines = new_lines;
		if (ft_strlen(*lines) > 0)
			return (temp);
	}
	else 
		temp = ft_strdup(*lines);
	free(*lines);
	*lines = NULL;
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*lines;
	char		*buffer;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
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
			append_buffer(&lines, buffer);
		}
	}
	free(buffer);
	if(lines != NULL && ft_strlen(lines) < 1 && read_bytes == 0)
		return (NULL);
	return get_line(&lines);
}
/* int main(int ac, char **av) { */
/*     int fd = open("test.txt", O_RDONLY); */
/* 	(void)ac; */
/* 	av++; */
/* 	char	*temp; */
/* 	while ((temp = get_next_line(fd))!= NULL) */
/* 		printf("%s", temp); */
/* 	/1* printf("DIFF:%d\n", strcmp(temp, "0123456789012345678901234567890123456789\n")); *1/ */
/* 	/1* printf("DIFF:%d\n", strcmp(temp, "0123456789012345678901234567890123456789\n")); *1/ */
/* 	/1* printf("<START>%s<END>", temp); *1/ */
/* 	if (get_next_line(fd) == NULL) */
/* 		puts("OUTPUT IS NULL"); */
/*    close(fd); */
/* } */
