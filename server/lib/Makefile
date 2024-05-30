##
## EPITECH PROJECT, 2024
## teams
## File description:
## Makefile
##

CC = gcc

SRC =   str/str.c\
		str/new.c\
		str/add.c\
		str/convert.c\
		json/parser.c\
		json/utils.c\
		json/types/array.c\
		json/types/string.c\
		json/types/boolean.c\
		json/types/number.c\
		json/types/object.c\
		json/dump.c\
		json/checker.c\
		json/file.c\
		json/free.c\
		logger/logger.c\

NAME = ../libmy.a

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra -Wno-unused-function -g3
CPPFLAGS += -iquote ../include

all: $(NAME)

$(NAME): $(OBJ)
	ar rc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

debug: CFLAGS += -g3
debug: re

re: fclean all
