NAME=minishell

all:
	make -C libft/
	gcc  -Wall -Wextra -Werror -g -lncurses front/*.c front/*/*.c builtins/*.c back/*.c back/*/*.c -I includes libft/libft.a -o $(NAME)

clean:
	make clean -C libft/
	rm -rf srcs/*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

test: re
	# bash tests/42ShellTester.sh $(PWD)/$(NAME) --hard --reference "bash" --filter "tilde-expansion"
	bash tests/42ShellTester.sh $(PWD)/$(NAME) --hard --reference "bash" --filter $(NAME)
	bash test.sh

valgrind: re
	valgrind --leak-check=full ./minishell tests/tests_sh/test_pid.sh

.PHONY: all re clean fclean test valgrind