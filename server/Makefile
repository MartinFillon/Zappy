##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

CC = gcc
CFLAGS += -Wall -Wextra -D_GNU_SOURCE
CPPFLAGS += -iquote./include
LDLIBS += -L./ -lmy

NAME = ../zappy_server

SRC = $(BASE_SRC)
BASE_SRC = $(addsuffix .c, 				\
				$(addprefix src/, 			\
					init_program 			\
					$(addprefix cmd_line/, 	\
						display_help 			\
						handle_cmd_line 		\
						handle_nb_flags			\
						handle_name_flag		\
						log_level				\
					)\
					$(addprefix utils/,	\
						free_box		\
						va_free			\
						mod				\
						vec_cmp 		\
					)\
					$(addprefix game/, 		\
						$(addprefix map/, 	\
							initializer		\
							destroyer		\
							drop_on_tile	\
							take_on_tile	\
							get_tile		\
							display_map 	\
							send_info_tile 	\
						)\
						$(addprefix team/,	\
							egg				\
							team			\
						)\
						broadcast			\
						game 				\
					)\
					$(addprefix server/, 	\
						accept				\
					  	init_server			\
						zappy_server		\
						buffer 				\
						$(addprefix cmd/, 	\
							handle_cmds 	\
							handle_display 	\
						) 					\
					)						\
					$(addprefix gui/,		\
						map_size			\
						map_content			\
						team_names			\
						player				\
						time 				\
					)\
					$(addprefix client/, 	\
						init_client			\
						send	 			\
						ai_entrypoint	 	\
						gui_entrypoint	 	\
						parse_unset			\
						read_client			\
						close_client		\
					)						\
					$(addprefix time/, 	\
						clock				\
					)						\
					$(addprefix ai/, 	\
						init				\
						eat					\
						handle_look			\
						handle_forward		\
						handle_rotate		\
					)\
				)\
			)\

SRC += src/main.c

OBJ = $(SRC:.c=.o)

TEST_NAME = unit_tests
TEST_SRC =

all: lib $(NAME)

$(NAME): $(OBJ) blib
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

blib:
	$(MAKE) -C lib

clean:
	rm -f $(OBJ)
	rm -f *.gcno
	rm -f *.gcda
	$(MAKE) -C lib clean

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)
	$(MAKE) -C lib fclean

$(TEST_NAME): LDFLAGS += -lcriterion
$(TEST_NAME): $(BASE_SRC) $(TEST_SRC)
	$(CC) $(BASE_SRC) $(TEST_SRC) --coverage $(LDFLAGS) \
		-o $(TEST_NAME) $(CPPFLAGS) $(CFLAGS) $(LDLIBS)

tests_run:	lib $(TEST_NAME)
	./$(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re tests_run
