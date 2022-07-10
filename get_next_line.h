#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
/* # define BUFFER_SIZE 54 */ 
# define OPEN_MAX 256
# include <stdlib.h>
# include <unistd.h>

typedef struct{
    char *lines;
    int length;
} ft_lines;
char	*get_next_line(int fd);
int	ft_strlen(const char *str);
int ft_strchr(const char *s, int c);
char	*ft_strncpy(char *restrict dest, const char *restrict src, size_t n);
void	ft_lines_realloc(ft_lines **lines, int size);
# endif
