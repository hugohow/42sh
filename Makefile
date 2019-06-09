.PHONY: all test clean test
NAME=minishell

all:
	make -C libft/
	gcc  -lncurses -Wall -Wextra -Werror -g -I includes libft/libft.a shell.c front/*.c front/utils/*.c back/*.c back/*/*.c -o $(NAME)

clean:
	make clean -C libft/
	rm -rf srcs/*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

test:
	bash ~/42ShellTester/42ShellTester.sh /Users/hugohow-choong/42/minishell_21sh_42sh/$(NAME) --reference "bash" --filter $(NAME) > error | cat
	cat error | less