# .PHONY: all test clean test
NAME=minishell

all:
	make -C libft/
	gcc  -Wall -Wextra -Werror -g front/*.c back/*.c back/*/*.c shell.c -I includes libft/libft.a -o $(NAME)

clean:
	make clean -C libft/
	rm -rf srcs/*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

test: re
	bash 42ShellTester/42ShellTester.sh $(PWD)/$(NAME) --reference "bash" --filter $(NAME) > log