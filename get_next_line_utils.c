/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzarco-l <fzarco-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 02:40:39 by fzarco-l          #+#    #+#             */
/*   Updated: 2022/07/11 21:50:55 by fzarco-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (*str++)
		count++;
	return (count);
}

int	ft_strchr(char *lines, int c)
{
	int	i;

	if (!lines)
		return (-1);
	i = 0;
	while (lines[i] != '\0')
	{
		if (lines[i] == (char)c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

char	*ft_strncpy(char *dest, char *src, size_t n)
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

void	ft_realloc(char **lines, int size)
{
	char	*new;
	int		lines_len;

	lines_len = ft_strlen(*lines);
	new = malloc(sizeof(char) * (lines_len + size));
	if (!new)
		return ;
	ft_strncpy(new, *lines, lines_len);
	free(*lines);
	*lines = new;
}
