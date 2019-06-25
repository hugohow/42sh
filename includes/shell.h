/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 00:32:39 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/25 14:55:54 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <termios.h>
#include <sys/wait.h>
#include <termios.h>

#include <sys/ioctl.h>
#include <signal.h>
#include <curses.h>
#include <sys/uio.h>
#include <curses.h>
#include <term.h>

#include "libft.h"
#include "ht.h"
#include "ft_printf.h"
typedef struct termios t_config;


# define TYPE_BASE (1 << 0)
# define TYPE_CMD (1 << 1)
// # define TYPE_SEPARATOR (2 << 2)

# define BUF_SIZE 20
# define FLAG_CD_P (1 << 0)
# define FLAG_CD_L (1 << 1)
# define FLAG_ECHO_N (1 << 0)
# define EXIT_SUCCESS 0
# define EXIT_FAIL 1
# define EXIT_UTILITY_NOT_FOUND 127
# define NAME "\x1b[32mMinishell \x1b[0m"
# define PROMPT "\x1b[36m ➜ \x1b[0m"

# define KEY_TERM_ENTER 13
# define KEY_TERM_CTRL_C 3
# define KEY_TERM_CTRL_D 4
# define KEY_TERM_DEL 127
# define KEY_TERM_TAB 9


# define BUILTIN_CD "cd"
# define BUILTIN_ECHO "echo"
# define BUILTIN_ENV "env"
# define BUILTIN_EXIT "exit"
# define BUILTIN_SETENV "setenv"
# define BUILTIN_UNSETENV "unsetenv"

extern char **environ;

typedef struct s_token
{
    char *type;
    char* value;
}              t_token;

typedef struct s_node
{
    long	type;
    char *cmd;
	char **args;
    struct s_node **child;
}              t_node;

typedef struct s_env
{
    char *line;
	t_ht *table;
    int special;
}               t_env;


int ft_terminal_get_cmd(char **command, t_env **copy_env);
int ft_terminal_read_key(void);

int ft_terminal_exec(t_env ***p_copy_env);
void ft_terminal_prompt(void);
int ft_file_exec(t_env ***p_copy_env, char **argv);

t_node **get_child(char *cmd, t_env **copy_env);
t_node *create_node(long type, char *cmd, t_env **copy_env);
void    print_tree(t_node *node);

int is_separator(char *str);
int is_redirection(char *str);
int is_pipe(char *str);
void print_tokens(t_token **list);


int					get_next_line(const int fd, char **line);


/*
** Functions related to environnement variables
*/

char *ft_env_get_line(t_env **cpy_environ, char *str);
char *ft_env_get_line_n(t_env **cpy_environ, char *str, size_t n);
char *ft_env_get_value(t_env **cpy_environ, char *key);
int ft_env_delete_line(char *key, t_env **cpy_environ);
int ft_env_change_line(char *key, char *line, t_env **cpy_environ);
char **ft_env_raw(t_env **cpy_environ);
t_env **ft_env_copy_raw(char **str, char **argv);
void ft_env_add(char *prefix, char *line, t_env ***p_environ, int special);
int ft_env_cmp_prefix(char *prefix, char *line);
t_env **ft_env_deep_copy(t_env **str);
void ft_env_free(t_env ***p_cpy_environ);


/*
** Builtins
*/


int     ft_echo(char **argv, t_env **cpy_environ, int fds[]);
int     ft_cd(char **argv, t_env ***p_cpy_environ, int fds[]);
int 	ft_setenv(char **argv, t_env ***p_environ, int fds[]);
int 	ft_env(char **argv, t_env **cpy_environ, int fds[]);
int 	ft_unsetenv(char **argv, t_env **cpy_environ, int fds[]);
int 	ft_exit(char **argv, t_env **cpy_environ, int fds[]);




char *ft_env_autocomplete_cmd(char *begin, t_env **copy_env);
char *ft_path_trim(char *path);

void    print_normal(int fd);
void    ft_setenv_args(char *prefix, char *line, t_env ***p_environ);


int ft_list_size(char **list);
void ft_list_free(char **list);

int ft_is_path(char *cmd);
void ft_print_env(t_env **str, int fds[]);
int ft_terminal_init(t_config *old_config, t_config *new_config, t_env **copy_env);
void ft_terminal_exit(struct termios *orig_termios);
void print_cmd(char *cmd);
void add_to_stdout(char **p_cmd, int c, int *index);
void delete_n_lines(int n);
int count_nb_line(char *cmd);

int ft_exe_path(char *path, char **argv, t_env **cpy_environ, int fds[]);
int ft_ask_command(int fd, char **command);


t_node **ft_syntax_tree_create(char *cmd, t_env **copy_env);
void ft_syntax_tree_free(t_node **root);


int ft_exe_bin(t_node *node, t_env ***p_environ, int fds[]);
void    execute_tree(t_node *node, t_env ***p_environ, int fds[], int *p_success);
t_node **ft_get_semi_colon_child(char *cmd, t_env **copy_env);
t_ht *ft_bins_table_create(char *line);
t_ht * ft_bins_table_get(t_env **copy_environ);
char **ft_get_args(char *cmd, t_env **copy_env, int *p_result_parsing);
char *ft_get_args_dollar(char *str, t_env **copy_env, int *p_result_parsing);
char *ft_get_args_tilde(char *str, t_env **copy_env);
int	ft_isatty(int fd);
char *ft_node_join(t_list *head, int size);
char			**ft_str_separate(char const *str, char c);
#endif