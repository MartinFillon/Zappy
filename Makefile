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

clean:
	$(foreach M,$(MODULES), make -C $M $@;)

docs-clean:
	$(RM) -r doc/ai doc/gui doc/server

fclean: clean docs-clean
	$(foreach M,$(MODULES), make -C $M $@;)

re: fclean all

bonus: re
	$(MAKE) -C server/dashboard

docs: docs-clean
	$(MAKE) -C gui docs
	$(MAKE) -C server docs
	cargo doc --no-deps -p ai -p zappy-json -p zappy-macros
	cp -r target/doc doc/ai

tests_run: fclean
	$(MAKE) -C server unit_tests
	$(MAKE) -C server/core unit_tests
	$(MAKE) -C server/lib unit_tests
	./server/unit_tests
	./server/core/unit_tests
	./server/lib/unit_tests
	cargo +stable install cargo-llvm-cov --locked
	cargo llvm-cov --no-report
	# $(MAKE) coverage

coverage:
	$(MAKE) -C server coverage
	cargo llvm-cov report --open

.PHONY: clean fclean re tests_run docs
