##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

MODULES := gui server ai


all: zappy_gui zappy_server zappy_ai

zappy_%:
	@make -C $*

clean fclean tests_run:
	$(foreach M,$(MODULES), make -C $M $@;)

func_tests:
	$(MAKE) -C server func_tests

re: fclean all

.PHONY: clean fclean re tests_run
