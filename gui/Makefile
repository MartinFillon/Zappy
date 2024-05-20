##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++20

NAME = ../zappy_gui

SRC = $(BASE_SRC)
BASE_SRC = src/Main.cpp

OBJ = $(SRC:.cpp=.o)

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
