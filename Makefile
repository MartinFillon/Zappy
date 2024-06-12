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

clean tests_run:
	$(foreach M,$(MODULES), make -C $M $@;)

docs-clean:
	$(RM) -r doc/ai doc/gui doc/server

fclean: clean docs-clean
	$(foreach M,$(MODULES), make -C $M $@;)
	$(RM) $(FTESTBIN)

func_tests:
	cargo build --release -p $(FTEST) && cp $(FBIN) $(FTESTBIN)

re: fclean all

bonus: re
	$(MAKE) -C server/dashboard

docs: docs-clean
	$(MAKE) -C gui docs
	$(MAKE) -C server docs
	cargo doc --no-deps -p ai -p zappy-json -p zappy-macros
	cp -r target/doc doc/ai

.PHONY: clean fclean re tests_run docs
