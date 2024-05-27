##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror -D_GNU_SOURCE
CPPFLAGS = -iquote./include

NAME = ../zappy_server

SRC = $(BASE_SRC)
BASE_SRC = $(addsuffix .c, 				\
				$(addprefix src/, 			\
					$(addprefix cmd_line/, 	\
						display_help 			\
						handle_cmd_line 		\
						handle_nb_flags			\
						handle_name_flag		\
					)\
					$(addprefix utils/,	\
						logger_error	\
						free_box		\
						va_free			\
						mod				\
					)\
					$(addprefix map/, 	\
						initializer		\
						destroyer		\
						drop_on_tile	\
						take_on_tile	\
						display_map 	\
						send_info_tile 	\
						get_tile		\
					)\
          			$(addprefix queue/,   \
          			  	create              \
          			  	delete              \
          			  	push                \
          			  	pop                 \
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
					$(addprefix client/, 	\
						$(addprefix gui/,	\
							map_size		\
							map_content		\
							team_names		\
							player			\
							time 			\
						)\
						$(addprefix ai/,	\
							handle_foward 	\
							handle_rotate 	\
							handle_look 	\
						)\
						init_client			\
						send	 			\
						ai_entrypoint	 	\
						gui_entrypoint	 	\
						parse_unset			\
						read_client			\
						close_client		\
					)						\
				)\
			)\

SRC += src/main.c

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
$(TEST_NAME): $(BASE_SRC) $(TEST_SRC)
	$(CC) $(BASE_SRC) $(TEST_SRC) --coverage $(LDFLAGS) \
		-o $(TEST_NAME) $(CPPFLAGS) $(CFLAGS)

tests_run:	$(TEST_NAME)
	./$(TEST_NAME)

func_tests: $(NAME)
	$(MAKE) -C tests

re: fclean all

.PHONY: all clean fclean re tests_run
