##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

all: gui server ai

gui:
	@make -C gui

ai:
	@make -C ai

server:
	@make -C server

clean:
	@make clean -C gui
	@make clean -C ai
	@make clean -C server

fclean:
	@make fclean -C gui
	@make fclean -C ai
	@make fclean -C server

tests_run:
	@make tests_run -C gui
	@make tests_run -C ai
	@make tests_run -C server

re: fclean all

.PHONY: all clean fclean re gui ai server tests_run
