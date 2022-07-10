#include "get_next_line.h"

#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void append_buffer(char **lines, char *buffer, int size) {
    if (!*lines)
        *lines = malloc(sizeof(char) * BUFFER_SIZE);
    else
        ft_realloc(lines, size);
    char *p_line = *lines;
    while (*p_line) p_line++;
    while (*buffer) *p_line++ = *buffer++;
    *p_line = '\0';
}

char *get_line(char **lines) {
    if (!*lines) return (NULL);
    int index = ft_strchr(*lines, '\n');
    if (index < 0) return (NULL);
    char *temp = malloc(sizeof(char) * index + 2);
    ft_strncpy(temp, *lines, index + 1);
    temp[index + 1] = '\0';
    int n_length = ft_strlen(*lines) - index - 1;
    char *n_lines = malloc(sizeof(char) * n_length + 1);
    ft_strncpy(n_lines, *lines + index + 1, n_length);
    n_lines[n_length + 1] = '\0';
    free(*lines);
    *lines = n_lines;
    return (temp);
}

char *get_next_line(int fd) {
    int read_bytes;
    // initialize buffer
    char *buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
    char *line;
    static char *lines = NULL;

    // initialize line
    read_bytes = -1;
    while (read_bytes != 0 && ft_strchr(buffer, '\n') == -1) {
        read_bytes = read(fd, buffer, BUFFER_SIZE);
        buffer[read_bytes] = '\0';
        append_buffer(&lines, buffer, BUFFER_SIZE);
    }
    line = get_line(&lines);
    if (line) return (line);
    return (NULL);
}

int main(int ac, char **av) {
    int fd = open("test.txt", O_RDONLY);
    char *line;
    (void)ac;
    av++;
    while ((line = get_next_line(fd)) != NULL) printf("%s", line);
    close(fd);
}
