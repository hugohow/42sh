NAME=minishell


ifeq ($(shell uname),Darwin)
CFLAGS 		= 		 -Wall -Werror -Wextra -g -Iincludes  -l termcap 
else
CFLAGS 		= 		 -Wall -Wextra -g -Iincludes  -l ncurses
endif


all:
	make -C libft/
	gcc  $(CFLAGS) srcs/*.c srcs/front/*.c srcs/front/*/*.c srcs/builtins/*.c srcs/variables/*.c srcs/back/*.c srcs/back/*/*.c  libft/libft.a -o $(NAME)

clean:
	make clean -C libft/
	rm -rf srcs/*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

test: re
	# bash tests/42ShellTester.sh $(PWD)/$(NAME) --hard --reference "bash" --filter "tilde-expansion"
	bash tests/42ShellTester.sh $(PWD)/$(NAME) --hard --reference "csh" --filter $(NAME)
	bash test.sh

valgrind: re
	valgrind --track-origins=yes --show-leak-kinds=all --track-fds=yes 		\
				--show-reachable=no --leak-check=full ./minishell tests/tests_sh/test_cd.sh

.PHONY: all re clean fclean test valgrind