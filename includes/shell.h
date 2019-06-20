/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 00:32:39 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 18:01:51 by hhow-cho         ###   ########.fr       */
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


# define TYPE_BASE (2 << 0)
# define TYPE_CMD (2 << 1)
# define TYPE_SEPARATOR (2 << 1)

# define BUF_SIZE 20
# define FLAG_CD_P (2 << 0)
# define FLAG_CD_L (2 << 1)
# define FLAG_ECHO_N (2 << 0)
# define EXIT_SUCCESS 0
# define EXIT_FAIL 1
# define EXIT_UTILITY_NOT_FOUND 127

// interrupt = 0;
// # define FLAG_A (2 << 0)
// # define FLAG_B (2 << 1)
// # define FLAG_C (2 << 2)
// # define FLAG_D (2 << 3)
// # define FLAG_E (2 << 4)
// # define FLAG_F (2 << 5)
// # define FLAG_G (2 << 6)
// # define FLAG_H (2 << 7)
// # define FLAG_I (2 << 8)
// # define FLAG_J (2 << 9)
// # define FLAG_K (2 << 10)
// # define FLAG_L (2 << 11)
// # define FLAG_M (2 << 12)
// # define FLAG_N (2 << 13)
// # define FLAG_O (2 << 14)
// # define FLAG_P (2 << 15)
// # define FLAG_Q (2 << 16)
// # define FLAG_R (2 << 17)
// # define FLAG_S (2 << 18)
// # define FLAG_T (2 << 19)
// # define FLAG_U (2 << 20)
// # define FLAG_V (2 << 21)
// # define FLAG_W (2 << 22)
// # define FLAG_X (2 << 23)
// # define FLAG_Y (2 << 24)
// # define FLAG_Z (2 << 25)

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
    // pour la redirection
    int nb_pipe;
    int fd_origin;
    char *file_name;
    struct s_node **child;
}              t_node;

typedef struct s_env
{
    char *line;
	t_ht *table;
    int special;
}               t_env;


int ft_terminal_get_cmd(char **command);
int ft_terminal_read_key(void);

int shell_terminal(t_env ***p_copy_env);
int shell_file(t_env ***p_copy_env, char **argv);

t_node **get_child(char *cmd, t_env **copy_env);
t_node *create_node(long type, char *cmd, t_env **copy_env);
void    print_tree(t_node *node);

int is_separator(char *str);
int is_redirection(char *str);
int is_pipe(char *str);
void print_tokens(t_token **list);


int     get_next_line(const int fd, char **line);


char *ft_env_get_line(t_env **cpy_environ, char *str);
char *ft_env_get_line_n(t_env **cpy_environ, char *str, size_t n);
char *ft_env_get_value(t_env **cpy_environ, char *key);
int ft_env_delete_line(char *key, t_env **cpy_environ);
int ft_env_change_line(char *key, char *line, t_env **cpy_environ);
char **ft_env_raw(t_env **cpy_environ);
t_env **ft_env_copy_raw(char **str, char **argv);
void ft_env_add(char *prefix, char *line, t_env ***p_environ);
int ft_env_cmp_prefix(char *prefix, char *line);
char *ft_path_trim(char *path);

void    print_normal(int fd);
void    ft_setenv_args(char *prefix, char *line, t_env ***p_environ);


int     ft_echo(int argc, char **argv, t_env **cpy_environ, int fds[]);
int     ft_cd(int argc, char **argv, t_env **cpy_environ, int fds[]);
int ft_setenv(int argc, char **argv, t_env ***p_environ, int fds[]);
int ft_env(int argc, char **argv, t_env **cpy_environ, int fds[]);
int ft_unsetenv(int argc, char **argv, t_env **cpy_environ, int fds[]);
int ft_exit(int argc, char **argv, t_env **cpy_environ, int fds[]);



void ft_print_env(t_env **str, int fds[]);
int ft_terminal_init(struct termios *orig_termios, struct termios *new_termios);
void ft_terminal_exit(struct termios *orig_termios);
void print_cmd(char *cmd);
void add_to_stdout(char **p_cmd, int c, int *index);
void delete_n_lines(int n);
int count_nb_line(char *cmd);
t_node **ft_syntax_tree_create(char *cmd, t_env **copy_env);
int ft_exe_path(char *path, char **argv, t_env **cpy_environ, int fds[]);
int ft_ask_command(int fd, char **command);

t_env **ft_env_deep_copy(t_env **str);
void ft_env_free(t_env ***p_cpy_environ);
int ft_exe_bin(t_node *node, t_env ***p_environ, int fds[]);
void    execute_tree(t_node *node, t_env ***p_environ, int fds[], int *p_success);
t_node **ft_get_semi_colon_child(char *cmd, t_env **copy_env);
t_ht *ft_bins_table_create(char *line);
char **ft_get_args(char *cmd, t_env **copy_env);
char *ft_get_args_dollar(char *str, t_env **copy_env);
char *ft_get_args_tilde(char *str, t_env **copy_env);
int	ft_isatty(int fd);
#endif