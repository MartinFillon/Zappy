##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Wall -Wextra -fPIC
CPPFLAGS = -iquote../include
LDLIBS = -lraylib -L.. -lmy -lcore

SRC = src/base.c

OBJ = $(SRC:.c=.o)

NAME = ../base.so

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ) $(LDLIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
