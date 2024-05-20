##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++20

NAME = ../zappy_gui

SRC = src/Main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
