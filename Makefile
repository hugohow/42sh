# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/04 22:12:22 by hhow-cho          #+#    #+#              #
#    Updated: 2019/07/08 22:54:09 by hhow-cho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 		=		minishell
CC			= 		gcc
CFLAGS 		= 		-Wall -Werror -Wextra -g -Iincludes
OBJ 		= 		$(SRC:.c=.o)

C_OK		=		"\033[35m"
C_GOOD		=		"\033[32m"
C_NO		=		"\033[00m"

SUCCESS		=		$(C_GOOD)SUCCESS$(C_NO)
OK			=		$(C_OK)OK$(C_NO)

DEBUG = #-g3 -fsanitize=address

SRC =	srcs/main.c							\
		srcs/ft_interactive_exec.c			\
		srcs/ft_non_interactive_exec.c		\
		srcs/back/ft_cmd_exec.c				\
		srcs/back/ft_exe_bin.c				\
		srcs/back/ft_exe_path.c				\
		srcs/back/ft_syntax_tree_create.c	\
		srcs/back/ft_syntax_tree_execute.c	\
		srcs/back/ft_syntax_tree_free.c		\
		srcs/back/parsing/ft_args_dollar_get.c	\
		srcs/back/parsing/ft_args_dollar_is_valid.c	\
		srcs/back/parsing/ft_args_dollar_replace_expansion.c	\
		srcs/back/parsing/ft_args_get.c	\
		srcs/back/parsing/ft_args_tilde_get.c	\
		srcs/back/parsing/ft_get_semi_colon_child.c	\
		srcs/back/utils/ft_bin_is_accessible.c	\
		srcs/back/utils/ft_bins_table_create.c	\
		srcs/back/utils/ft_bins_table_get.c	\
		srcs/back/utils/ft_env_add.c	\
		srcs/back/utils/ft_env_autocomplete_cmd.c	\
		srcs/back/utils/ft_env_autocomplete_sugg.c	\
		srcs/back/utils/ft_env_change_line.c	\
		srcs/back/utils/ft_env_cmp_prefix.c	\
		srcs/back/utils/ft_env_copy_raw.c	\
		srcs/back/utils/ft_env_copy_utils.c	\
		srcs/back/utils/ft_env_deep_copy.c	\
		srcs/back/utils/ft_env_delete_line.c	\
		srcs/back/utils/ft_env_free.c	\
		srcs/back/utils/ft_env_get_line.c	\
		srcs/back/utils/ft_env_raw.c	\
		srcs/back/utils/ft_errors_signal_get.c	\
		srcs/back/utils/ft_is_path.c	\
		srcs/back/utils/ft_isatty.c	\
		srcs/back/utils/ft_list_free.c	\
		srcs/back/utils/ft_list_size.c	\
		srcs/back/utils/ft_path_trim.c	\
		srcs/back/utils/ft_path_trim_free.c	\
		srcs/back/utils/ft_str_separate.c	\
		srcs/back/utils/ft_strjoin_.c	\
		srcs/back/utils/ft_strjoin_free_first.c	\
		srcs/back/utils/ft_strjoin_free_second.c	\
		srcs/builtins/ft_cd.c	\
		srcs/builtins/ft_cd_get_abs_path_cdpath.c	\
		srcs/builtins/ft_cd_get_dest_path.c	\
		srcs/builtins/ft_cd_get_dst_path_utils.c	\
		srcs/builtins/ft_cd_get_pwd_plus_element.c	\
		srcs/builtins/ft_cd_go_to.c		\
		srcs/builtins/ft_cd_parse.c			\
		srcs/builtins/ft_echo.c			\
		srcs/builtins/ft_env.c			\
		srcs/builtins/ft_env_complete_env.c			\
		srcs/builtins/ft_env_parse.c			\
		srcs/builtins/ft_exit.c			\
		srcs/builtins/ft_setenv.c			\
		srcs/builtins/ft_unsetenv.c			\
		srcs/front/ft_interactive_exit.c 		\
		srcs/front/ft_interactive_get_cmd.c			\
		srcs/front/ft_interactive_init.c			\
		srcs/front/ft_interactive_prompt.c		\
		srcs/front/ft_interactive_read_key.c		\
		srcs/front/ft_non_interactive_get_cmd.c		\
		srcs/front/ft_press_key/ft_apply_ctrl_c.c		\
		srcs/front/ft_press_key/ft_apply_ctrl_d.c		\
		srcs/front/ft_press_key/ft_apply_del.c			\
		srcs/front/ft_press_key/ft_apply_enter.c		\
		srcs/front/ft_press_key/ft_apply_key.c			\
		srcs/front/ft_press_key/ft_apply_printable.c		\
		srcs/front/ft_press_key/ft_apply_tab.c			\
		srcs/front/utils/ft_node_join.c					\
		srcs/variables/ft_vars_free.c					\
		srcs/variables/ft_vars_get.c					\
		srcs/variables/ft_vars_get_copy_env.c				\
		srcs/variables/ft_vars_init.c

all: $(NAME)


%.o: %.c
	@printf "[$(NAME)] Compiling [.:]\r"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "[$(NAME)] Compiling [:.]\r"

$(NAME): $(OBJ)
	@make -C libft/
	@echo "Creating" [ $(NAME) ]
	@$(CC) $(CFLAGS) -ltermcap $(INCLUDES) $^ libft/libft.a -o $(NAME)
	@echo "Creation" [ $(NAME) ] $(SUCCESS)

clean:
	@make clean -C libft/
	@/bin/rm -f $(OBJ)
	@printf "[$(NAME)] Removed object files!\n"

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft/
	@echo "Cleaning" [ $(NAME) ] "..." $(OK)
	
re: fclean all

test: re
	bash tests/42ShellTester.sh $(PWD)/$(NAME) --hard --reference "bash" --filter $(NAME)
	bash test.sh

.PHONY: all clean fclean re test