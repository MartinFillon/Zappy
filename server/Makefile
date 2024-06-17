##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

CC = gcc
CFLAGS += -Wall -Wextra -D_GNU_SOURCE
CPPFLAGS += -iquote./include
LDLIBS += -L./ -lcore -lm

NAME = ../zappy_server

SRC = $(BASE_SRC)
BASE_SRC = $(addsuffix .c, 				\
				$(addprefix src/, 			\
					init_program 			\
					destroy_program 		\
					loop 					\
					loader					\
				)\
			)

DISPLAYERS = base

SUBMODULES = lib core $(DISPLAYERS)

SRC += src/main.c

OBJ = $(SRC:.c=.o)

TEST_NAME = unit_tests
TEST_SRC =

all: submodules $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDLIBS)

submodules:
	$(foreach submodule, $(SUBMODULES), $(MAKE) -C $(submodule);)

clean:
	rm -f $(OBJ)
	rm -f *.gcno
	rm -f *.gcda
	$(foreach submodule, $(SUBMODULES), $(MAKE) -C $(submodule) clean;)
	$(MAKE) -C dashboard clean

docs-clean:
	$(RM) -r doc

fclean: clean docs-clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)
	$(foreach submodule, $(SUBMODULES), $(MAKE) -C $(submodule) fclean;)
	$(MAKE) -C dashboard fclean

$(TEST_NAME): LDFLAGS += -lcriterion
$(TEST_NAME): blib $(BASE_SRC) $(TEST_SRC)
	$(CC) $(BASE_SRC) $(TEST_SRC) --coverage $(LDFLAGS) \
		-o $(TEST_NAME) $(CPPFLAGS) $(CFLAGS) $(LDLIBS)

tests_run:	lib $(TEST_NAME)
	./$(TEST_NAME)

debug_submodules:
	$(foreach submodule, $(SUBMODULES), $(MAKE) -C $(submodule) debug;)

debug: CC = clang
debug: CFLAGS += -g3
#debug: LDFLAGS += -fsanitize=addres
debug: fclean debug_submodules all

re: fclean all

docs: docs-clean
	doxygen Doxyfile
	mv doc/html ../doc/server

.PHONY: all clean fclean re tests_run docs
