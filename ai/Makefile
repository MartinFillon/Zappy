##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

NAME = ../zappy_ai

BIN = ai

SRC =	src/main.rs

all: $(NAME)

$(NAME): $(SRC)
	cargo build --release --offline && cp ../target/release/$(BIN) $(NAME)

clean:
	cargo clean

fclean: clean
	rm -f $(NAME)

tests_run:
	cargo test

re: fclean all

.PHONY: all re clean fclean tests_run
