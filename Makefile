##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

MODULES := gui server ai

FUNC_TESTER := server-tester
FUNC_TESTER_BIN := $(FUNC_TESTER)-bin
FUNC_TESTER_PATH := target/release/$(FUNC_TESTER)


all: zappy_gui zappy_server zappy_ai

zappy_%:
	@make -C $*

clean fclean tests_run:
	$(foreach M,$(MODULES), make -C $M $@;)

func_tests:
	cargo build --release -p $(FUNC_TESTER)
		&& cp $(FUNC_TESTER_PATH) $(FUNC_TESTER_BIN)

re: fclean all

.PHONY: clean fclean re tests_run
