/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzarco-l <fzarco-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 02:36:03 by fzarco-l          #+#    #+#             */
/*   Updated: 2022/07/12 13:48:10 by fzarco-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define OPEN_MAX 256
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> //TODO REMOVE
# include <string.h> //TODO REMOVE
# include <fcntl.h>
# include <limits.h>
# include <sys/stat.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		ft_strlen(const char *str);
int		ft_strchr(char *lines, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
#endif
