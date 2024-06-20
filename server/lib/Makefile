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
		str/join.c\
		json/parser.c\
		json/utils.c\
		json/types/array.c\
		json/types/string.c\
		json/types/boolean.c\
		json/types/number.c\
		json/types/object.c\
		json/dump.c\
		json/file.c\
		json/free.c\
		logger/logger.c\
		utils/free_box.c\
		utils/va_free.c\
		utils/mod.c\
		utils/vec_cmp.c\
		utils/is_empty.c\
		utils/is_number.c\
		utils/is_coord_equals.c\
		options/parser.c\
		options/getters.c\
		options/defaults.c\
		options/required.c\
		options/converters/string.c\
		options/converters/int.c\
		options/converters/uint.c\
		options/converters/boolean.c\
		options/converters/float.c\
		options/converters/string_list.c\
		options/help.c\
		utils/freeze_ai.c

TEST_SRC = ../tests/lib/logger.spec.c\
			../tests/lib/str.spec.c\
			../tests/lib/json.spec.c\
			../tests/lib/options.spec.c\
			../tests/lib/utils.spec.c

TEST_OBJ = $(TEST_SRC:.c=.o)

NAME = ../libcore.a

TEST_NAME = unit_tests

OBJ = $(SRC:.c=.o)

SRC_GCNOS = $(SRC:.c=.gcno)
SRC_GCDA = $(SRC:.c=.gcda)
TEST_GCDA = $(TEST_SRC:.c=.gcda)
TEST_SRC_GCNOS = $(TEST_SRC:.c=.gcno)


CFLAGS += -Wall -Wextra -Wno-unused-function -fPIC
CPPFLAGS += -iquote ../include

all: $(NAME)

$(NAME): $(OBJ)
	ar cq -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f $(TEST_OBJ)
	rm -f $(SRC_GCNOS)
	rm -f $(SRC_GCDA)
	rm -f $(TEST_GCDA)
	rm -f $(TEST_SRC_GCNOS)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

debug: CC = clang
debug: CFLAGS += -g3
debug: all

$(TEST_NAME): CFLAGS += --coverage -DTEST
$(TEST_NAME): LDFLAGS += -lcriterion -lgcov
$(TEST_NAME): CPPFLAGS += -iquote .
$(TEST_NAME): fclean $(OBJ) $(TEST_OBJ)
	$(CC) -o $(TEST_NAME) $(TEST_OBJ) $(OBJ) $(LDFLAGS)

tests_run: $(TEST_NAME)
	./$(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re debug
