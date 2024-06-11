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
		src/displayers/id.c 	\
		src/displayers/team.c	\
		src/displayers/inventory.c	\
		src/displayers/level.c	\
		src/events.c 			\
		src/event_handlers/keys/left.c	\
		src/event_handlers/keys/right.c	\

OBJ = $(SRC:.c=.o)

NAME = ../dashboard.so

all: lib $(NAME)

$(NAME): $(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ) $(LDLIBS)

lib:
	$(MAKE) -C ../lib

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
