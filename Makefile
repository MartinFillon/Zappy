##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

MODULES := gui server ai

FTEST := server-tester
FTESTBIN := $(FTEST)-bin
FBIN := target/release/$(FTEST)


all: zappy_gui zappy_server zappy_ai

zappy_%:
	@make -C $*

clean fclean tests_run:
	$(foreach M,$(MODULES), make -C $M $@;)

func_tests:
	cargo build --release -p $(FTEST) && cp $(FBIN) $(FTESTBIN)

re: fclean all

.PHONY: clean fclean re tests_run
