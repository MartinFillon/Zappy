##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

NAME = ../zappy_ai

BIN = ai

BPATH = ../target/release/$(BIN)

all: $(NAME)

$(NAME):
	cargo build --release -p ai && cp $(BPATH) $(NAME)

clean:
	cargo clean
	rm -rf cargo-test* json/cargo-test* macros/cargo-test* ../server/tests/server-tester/cargo-test*

fclean: clean
	rm -f $(NAME)

tests_run:
	cargo +stable install cargo-llvm-cov --locked
	cargo llvm-cov

re: fclean all

.PHONY: all re clean fclean tests_run
