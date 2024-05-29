##
## EPITECH PROJECT, 2024
## logger
## File description:
## Makefile
##

CC ?= gcc
CFLAGS = -Wall -Wextra
CPPFLAGS = -I../include

SRC =	src/logger.c

OBJ = $(SRC:.c=.o)

NAME = ../liblogger.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
