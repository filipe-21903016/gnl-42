/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzarco-l <fzarco-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 02:36:03 by fzarco-l          #+#    #+#             */
/*   Updated: 2022/07/11 21:08:45 by fzarco-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define OPEN_MAX 256
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> //TODO REMOVE
# include <fcntl.h>
# include <limits.h>
# include <sys/stat.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		ft_strlen(const char *str);
int		ft_strchr(char *lines, int c);
char	*ft_strncpy(char *dest, char *src, size_t n);
void	ft_realloc(char **lines, int size);
#endif
