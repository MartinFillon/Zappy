##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Wall -Wextra -fPIC
CPPFLAGS = -iquote../include
LDLIBS = -L.. -lcore

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

debug: CC = clang
debug: CFLAGS += -g3 -fsanitize=address
debug: LDFLAGS += -fsanitize=addres
debug: fclean all

re: fclean all

.PHONY: all clean fclean re debug
