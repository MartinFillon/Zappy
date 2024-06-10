##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Wall -Wextra -fPIC -D_GNU_SOURCE
CPPFLAGS = -iquote../include
LDLIBS = -lraylib -L.. -lmy

SRC = 	src/dashboard.c			\
		src/waiting.c			\
		src/display_clients.c	\

OBJ = $(SRC:.c=.o)

NAME = ../dashboard.so

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ) $(LDLIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
