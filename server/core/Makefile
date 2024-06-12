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
					$(addprefix cmd_line/, 	\
						display_help 			\
						handle_cmd_line 		\
						handle_nb_flags			\
						handle_name_flag		\
						log_level				\
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
							handle_cmds 	\
							handle_display 	\
							handle_ais_info	\
							handle_eggs_info\
							handle_help 	\
							handle_kill_player 	\
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
					)						\
					$(addprefix ai/, 	\
						init				\
						eat					\
						handle_look			\
						handle_forward		\
						handle_rotate		\
						handle_broadcast 	\
						handle_take_object 	\
						handle_set_object 	\
						handle_inventory 	\
						handle_connect_nbr 	\
						handle_fork 		\
						handle_eject 		\
						handle_incantation 	\
						destroy				\
					)\
					$(addprefix router/, 	\
						mode_parser			\
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

NAME = ../libcore.so

all: $(NAME)

$(NAME): lib $(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ) $(LDLIBS)

lib:
	$(MAKE) -C ../lib

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
