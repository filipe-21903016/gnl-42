#include "get_next_line.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>


void    append_buffer(ft_lines **lines, char *buffer)
{
    int n;
    int b_length;
    b_length = ft_strlen(buffer);
    /* Initialize lines struture */
    if (!*lines)
    {
        *lines = malloc(sizeof(ft_lines));
        if (!*lines)
            return ;
        (*lines)->lines = malloc(sizeof(char) * b_length);
        if (!(*lines)->lines )
            return ;
        (*lines)->length = 0;
    }
    /* lines already initialized */
    else
       ft_lines_realloc(lines, b_length); 
    /* Copiar do buffer para lines */
    ft_strncpy((*lines)->lines, buffer, b_length);

    /* atualizar tamanho de lines */
    n = (*lines)->length; 
    (*lines)->length = n + b_length;
}

char *get_next_line(int fd) {
    static ft_lines *lines;
    char *buffer;
    int read_bytes;

    lines = NULL;
    read_bytes = -1;
    buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    
    //read to buffer
    read_bytes = read(fd, buffer, BUFFER_SIZE);
    //put \0 at the end of buffer
    buffer[read_bytes] = '\0';
    //copy to lines without null chars


    //free buffer
    free(buffer);
    return NULL;
}

int main(int ac, char **av) {
    int fd = open("test.txt", O_RDONLY);
    char *line;
	(void)ac;
	av++;
    /* while ((line = get_next_line(fd)) != NULL) */ 
        /* printf("%s", line); */
    static ft_lines *lines;
    char buffer[BUFFER_SIZE];
    lines = NULL;
    int read_b = read(fd, buffer, BUFFER_SIZE);
    buffer[read_b] = '\0';
    append_buffer(&lines, buffer);
    printf("%s | %d", lines->lines,lines->length);


    close(fd);
}
