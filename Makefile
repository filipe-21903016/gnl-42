SRC = get_next_line.c get_next_line_utils.c

all:
	gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 $(SRC)

clean:
	rm -rf a.out
