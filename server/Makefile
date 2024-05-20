##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -iquote./include

NAME = ../zappy_server

SRC = $(BASE_SRC)
BASE_SRC = 	src/main.c\
			src/queue/create.c\
			src/queue/delete.c\
			src/queue/push.c\
			src/queue/pop.c

OBJ = $(SRC:.c=.o)

TEST_NAME = unit_tests
TEST_SRC =

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f *.gcno
	rm -f *.gcda

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

$(TEST_NAME): LDFLAGS += -lcriterion
$(TEST_NAME): $(SRC) $(TEST_SRC)
	$(CC) $(SRC) $(TEST_SRC) --coverage $(LDFLAGS) \
		-o $(TEST_NAME)

tests_run:	$(TEST_NAME)
	./$(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re tests_run
