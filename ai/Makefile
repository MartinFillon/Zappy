##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

NAME = ../zappy_ai

BIN = ai

BPTAH = ../target/release/$(BIN)

SRC =	src/main.rs

all: $(NAME)

$(NAME): $(SRC)
	cargo build --release -p ai && cp $(BPATH) $(NAME)

clean:
	cargo clean

fclean: clean
	rm -f $(NAME)

tests_run:
	cargo test

re: fclean all

.PHONY: all re clean fclean tests_run
