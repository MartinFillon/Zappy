##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude/
LDFLAGS = -lraylib -lpthread

NAME = ../zappy_gui

SRC = $(BASE_SRC) 						\
	$(addsuffix .cpp,					\
		$(addprefix src/,				\
			$(addprefix ArgParser/,		\
				ArgParser				\
			)							\
			$(addprefix Network/,		\
				Handler					\
				Handler_queries         \
			)							\
			$(addprefix GUI/,			\
				$(addprefix Data/,		\
					Inventory			\
					Map					\
					Player				\
				)						\
				Raylib					\
				Display					\
				ServerMessageHandler	\
				MessageBox				\
				InfoBox					\
				TimeUnitInput			\
			)							\
		)								\
	)
BASE_SRC = src/main.cpp

OBJ = $(SRC:.cpp=.o)

TEST_NAME = unit_tests
TEST_SRC =

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)
	rm -f *.gcno
	rm -f *.gcda

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

$(TEST_NAME): LDFLAGS += -lcriterion
$(TEST_NAME): $(SRC) $(TEST_SRC)
	$(CXX) $(SRC) $(TEST_SRC) --coverage $(LDFLAGS) \
		-o $(TEST_NAME)

tests_run:	$(TEST_NAME)
	./$(TEST_NAME) -h 123 -p 123123

re: fclean all

docs: docs-clean
	doxygen Doxyfile && mv doc/html ../doc/gui

debug: CXXFLAGS += -g3
debug: re

.PHONY: all clean fclean re tests_run debug docs docs-clean
