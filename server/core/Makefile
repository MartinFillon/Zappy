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

NAME = ../libcore.a

all: $(NAME)

$(NAME): $(OBJ)
	ar cq -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

debug: CC = clang
debug: CFLAGS += -g3
debug: all

re: fclean all

.PHONY: all clean fclean re
