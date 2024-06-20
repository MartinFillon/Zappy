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

TEST_SRC = ../tests/server/loader.spec.c

TEST_OBJ = $(TEST_SRC:.c=.o)
NO_MAIN_OBJ = $(BASE_SRC:.c=.o)
NO_MAIN_GCNO = $(NO_MAIN_OBJ:.o=.gcno)
NO_MAIN_GCDA = $(NO_MAIN_OBJ:.o=.gcda)
TEST_GCNO = $(TEST_OBJ:.o=.gcno)
TEST_GCDA = $(TEST_OBJ:.o=.gcda)

SRC += src/main.c

OBJ = $(SRC:.c=.o)

TEST_NAME = unit_tests

all: submodules $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDLIBS)

submodules:
	$(foreach submodule, $(SUBMODULES), $(MAKE) -C $(submodule);)

clean:
	$(RM) $(OBJ)
	$(RM) $(NO_MAIN_GCNO)
	$(RM) $(NO_MAIN_GCDA)
	$(RM) $(TEST_GCNO)
	$(RM) $(TEST_GCDA)
	$(RM) $(TEST_OBJ)
	$(foreach submodule, $(SUBMODULES), $(MAKE) -C $(submodule) clean;)
	$(MAKE) -C dashboard clean

docs-clean:
	$(RM) -r doc

fclean: clean docs-clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)
	$(foreach submodule, $(SUBMODULES), $(MAKE) -C $(submodule) fclean;)
	$(MAKE) -C dashboard fclean

$(TEST_NAME): LDLIBS += -lcriterion -lgcov
$(TEST_NAME): CFLAGS += --coverage
$(TEST_NAME): clean submodules $(NO_MAIN_OBJ) $(TEST_OBJ)
	$(CC) $(NO_MAIN_OBJ) $(TEST_OBJ) $(LDLIBS) -o $(TEST_NAME)

tests_run: fclean
	$(MAKE) -C lib unit_tests
	# $(MAKE) $(TEST_NAME)
	$(MAKE) -C lib tests_run
	# ./$(TEST_NAME)

debug_submodules:
	$(foreach submodule, $(SUBMODULES), $(MAKE) -C $(submodule) debug;)

debug: CC = clang
debug: CFLAGS += -g3
debug: fclean debug_submodules all

sanitize: CC = clang
sanitize: CFLAGS += -g3 -fsanitize=address
sanitize: LDLIBS += -fsanitize=address
sanitize: fclean debug_submodules all

re: fclean all

docs: docs-clean
	doxygen Doxyfile
	mv doc/html ../doc/server

.PHONY: all clean fclean re tests_run docs
