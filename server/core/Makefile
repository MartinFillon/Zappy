##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Wall -Wextra -fPIC
CPPFLAGS = -iquote../include
LDLIBS = -L.. -lmy -lm

SRC = $(addsuffix .c, 				\
				$(addprefix src/, 			\
					core					\
					$(addprefix game/, 		\
						$(addprefix map/, 	\
							initializer		\
							destroyer		\
							drop_on_tile	\
							take_on_tile	\
							get_tile		\
							display_map 	\
							send_info_tile 	\
							verif_tile_requirement	\
						)\
						$(addprefix team/,	\
							egg				\
							team			\
						)\
						broadcast			\
						game 				\
						end					\
						refill				\
					)\
					$(addprefix server/, 	\
						accept				\
					  	init_server			\
						zappy_server		\
						buffer 				\
						destroy_server		\
						execute 			\
						$(addprefix cmd/, 	\
							cmds 	\
							display 	\
							ais_info	\
							eggs_info\
							help 	\
							kill_player 	\
							godmode			\
							give			\
							teleport		\
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
						parse_unset			\
						read_client			\
						close_client		\
						send_message_to_guis\
						prepare_res 		\
						kill_ai 			\
					)						\
					$(addprefix time/, 	\
						clock				\
						tick				\
					)						\
					$(addprefix ai/, 	\
						init				\
						eat					\
						$(addprefix commands/,\
							look			\
							forward		\
							rotate		\
							broadcast 	\
							take_object 	\
							set_object 	\
							inventory 	\
							connect_nbr 	\
							fork 		\
							eject 		\
							incantation_start 	\
							incantation_end 	\
						)\
						destroy				\
					)\
					$(addprefix router/, 	\
						init_router			\
						destroy_router		\
						run 				\
					)\
					$(addprefix middleware/,\
						invalid				\
					)\
				)\
			)\

OBJ = $(SRC:.c=.o)

NAME = ../libcore.a

TEST_SRC =  ../../tests/server/core.spec.c\
			../../tests/server/fake_server.c\
			../../tests/server/ai.spec.c\
			../../tests/server/gui.spec.c\


TEST_NAME = unit_tests

TEST_OBJ = $(TEST_SRC:.c=.o)

SRC_GCDA = $(SRC:.c=.gcda)
SRC_GCNOS = $(SRC:.c=.gcno)
TEST_GCDA = $(TEST_SRC:.c=.gcda)
TEST_GCNOS = $(TEST_SRC:.c=.gcno)

all: $(NAME)

$(NAME): $(OBJ)
	ar cq -o $(NAME) $(OBJ)

lib-test:
	$(MAKE) -C ../lib

$(TEST_NAME): CFLAGS += --coverage -DTEST
$(TEST_NAME): LDFLAGS += -lcriterion -lgcov -lm -L../ -lcore
$(TEST_NAME): CPPFLAGS += -iquote .
$(TEST_NAME): fclean lib-test $(OBJ) $(TEST_OBJ)
	$(CC) -o $(TEST_NAME) $(TEST_OBJ) $(OBJ) $(LDFLAGS)

tests_run: $(TEST_NAME)
	./$(TEST_NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(TEST_OBJ)
	$(RM) $(SRC_GCDA)
	$(RM) $(SRC_GCNOS)
	$(RM) $(TEST_GCDA)
	$(RM) $(TEST_GCNOS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST_NAME)

debug: CC = clang
debug: CFLAGS += -g3
debug: all

re: fclean all

.PHONY: all clean fclean re
