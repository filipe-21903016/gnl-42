#include "get_next_line.h"
#include "stdio.h"

int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (*str++)
		count++;
	return (count);
}

int ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

char *ft_strncpy(char *restrict dest, const char *restrict src, size_t n) {
  size_t i;
  char *ptr;

  i = 0;
  ptr = dest;
  while (src[i] != '\0' && i < n)
    *ptr++ = src[i++];
  while (i++ < n)
    *ptr++ = '\0';
  return (dest);
}

void	ft_lines_realloc(ft_lines **lines, int size)
{
	char	*new;

	new = malloc(sizeof(char) * ((*lines)->length + size));
	if (!new)
		return ;
	ft_strncpy(new, (*lines)->lines, (*lines)->length);
	free((*lines)->lines);
	(*lines)->lines = new;
}

