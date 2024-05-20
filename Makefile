##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

all: gui server # ai

gui server ai:
	@make -C $@

clean fclean tests_run:
	@make $@ -C gui
	# @make $@ -C ai
	@make $@ -C server

re: fclean all

.PHONY: all clean fclean re gui ai server tests_run
