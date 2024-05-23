##
## EPITECH PROJECT, 2024
## 201yams
## File description:
## Makefile
##

BIN = server-tester
NAME =  ../../../$(BIN)-bin

all: $(NAME)

$(NAME):
	cargo build --release && cp ./target/release/$(BIN) $(NAME)

clean:
	cargo clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean $(NAME)
