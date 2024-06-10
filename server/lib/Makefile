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
		str/split.c\
		str/convert.c\
		str/free.c\
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
		utils/free_box.c\
		utils/va_free.c\
		utils/mod.c\
		utils/vec_cmp.c\
		utils/is_empty.c\
		utils/is_number.c\
		utils/is_coord_equals.c

NAME = ../libmy.a

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra -Wno-unused-function -fPIC
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
