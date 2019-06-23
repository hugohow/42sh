NAME=minishell

all:
	make -C libft/
	gcc  -Wall -Wextra -Werror -g -lncurses front/*.c builtins/*.c back/*.c back/*/*.c -I includes libft/libft.a -o $(NAME)

clean:
	make clean -C libft/
	rm -rf srcs/*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

test: re
	# bash tests/42ShellTester.sh $(PWD)/$(NAME) --hard --show-success --reference "bash" --filter "tilde-expansion"
	# bash tests/42ShellTester.sh $(PWD)/$(NAME) --hard --show-success --reference "bash" --filter $(NAME)
	bash test.sh

.PHONY: all re clean fclean test