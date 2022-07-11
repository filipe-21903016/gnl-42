/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzarco-l <fzarco-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 01:54:26 by fzarco-l          #+#    #+#             */
/*   Updated: 2022/07/11 02:22:07 by fzarco-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void	append_buffer(ft_lines **lines, char *buffer, int b_size)
{
  int	n;
  /* Initialize lines struture */
  if (!*lines)
	{
    *lines = malloc(sizeof(ft_lines));
    if (!*lines)
    	return;
    (*lines)->lines = malloc(sizeof(char) * b_size);
    if (!(*lines)->lines)
    	return;
    ft_strncpy((*lines)->lines, buffer, b_size);
    (*lines)->length = b_size;
	}
  /* lines already initialized */
  else
  {
    ft_lines_realloc(lines, b_size);
    ft_strncpy((*lines)->lines + (*lines)->length, buffer, b_size);
    (*lines)->length = (*lines)->length + b_size;
  }
}

char	*get_line(ft_lines **lines)
{
    char	*temp;
    char	*new_lines;
    int	i;
    int	new_length;
    
    /* encontrar \n nas linhas */
	i = ft_strchr((*lines)->lines, (*lines)->length, '\n');
	if (i < 0)
		return (NULL);
	/* criar linha para retornar */
	temp = malloc(sizeof(char) * i + 2);
	if (!temp)
		return (NULL);
	ft_strncpy(temp, (*lines)->lines, i + 1);
	temp[i + 1] = '\0';
	/* criar novas linhas excluindo a retirada */
	new_length = (*lines)->length - i - 1;
	new_lines = malloc(sizeof(char) * new_length);
	ft_strncpy(new_lines, (*lines)->lines + i + 1, new_length);
	free((*lines)->lines);
	(*lines)->lines = new_lines;
    /* atualizar o tamanho das linhas */
	(*lines)->length = new_length;
	return (temp);
}

char	*get_next_line(int fd) {
    static	ft_lines *lines;
    char	*line;
    char	*buffer;
    int	read_bytes;

    read_bytes = -1;
    buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buffer)
    	return (NULL);
    while (read_bytes != 0 && ft_strchr(buffer, ft_strlen(buffer), '\n') == -1)
    {
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[read_bytes] = '\0';
		append_buffer(&lines, buffer,read_bytes);
    }
	free(buffer);
	return (get_line(&lines));
}
/* int main(int ac, char **av) { */
/*     int fd = open("test.txt", O_RDONLY); */
/*     char *line; */
/* 	(void)ac; */
/* 	av++; */
/*     while ((line = get_next_line(fd)) != NULL) */
/*         printf("%s", line); */
/*     close(fd); */
/* } */
