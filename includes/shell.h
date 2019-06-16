/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 00:32:39 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 14:27:18 by hhow-cho         ###   ########.fr       */
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
#include "libft.h"
#include "ht.h"

# define TYPE_BASE (2 << 0)
# define TYPE_CMD (2 << 1)
# define TYPE_SEPARATOR (2 << 1)

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
    char *prefix;
    char *line;
    int special;
}               t_env;


t_node **get_child(char *cmd, t_env **copy_env);
t_node *create_node(long type, char *cmd, t_env **copy_env);
void    print_tree(t_node *node);

int is_separator(char *str);
int is_redirection(char *str);
int is_pipe(char *str);
void print_tokens(t_token **list);


int     get_next_line(const int fd, char **line);
int     ft_printf(const char* format, ...);


char *ft_get_line_env(t_env **cpy_environ, char *str);
char *ft_get_line_env_n(t_env **cpy_environ, char *str, size_t n);
void    print_normal(int fd);
int ft_change_line_env(char *key, char *line, t_env **cpy_environ);
void    ft_setenv_args(char *prefix, char *line, t_env ***p_environ);
int     ft_echo(int argc, char **argv, t_env **cpy_environ, int fds[]);
int     ft_cd(int argc, char **argv, t_env **cpy_environ, int fds[]);
int     ft_setenv(int argc, char **argv, t_env ***p_environ, int fds[]);
int ft_env(int argc, char **argv, t_env ***p_environ, int fds[], t_ht *table_bins);
int ft_unsetenv(int argc, char **argv, t_env **cpy_environ, int fds[]);
void ft_print_env(t_env **str, int fds[]);
int ft_delete_line_env(char *key, t_env **cpy_environ);
void    ft_exit_terminal(void);
int     ft_init_terminal(struct termios *orig_termios, struct termios *new_termios);
int     ft_read_key();
void print_cmd(char *cmd);
void add_to_stdout(char **p_cmd, int c, int *index);
void delete_n_lines(int n);
int count_nb_line(char *cmd);
t_node **ft_parse_cmd(char *cmd, t_env **copy_env);
int ft_exe_path(char *path, char **argv, t_env **cpy_environ, int fds[]);
int ft_ask_command(int fd, char **command);
void ft_exit(char *cmd, int success);
t_env **copy_environ(t_env **str);
t_env **copy_environ_from_str(char **str);
char **get_env_tab_str(t_env **cpy_environ);
char **get_paths(t_env **copy_env);
int ft_exe_bin(t_node *node, t_ht *table_bins, t_env ***p_environ, int fds[]);
int is_exit(char *cmd);
int ft_get_cmd(int fd, char **command);
void    execute_tree(t_node *node, t_ht *table_bins, t_env ***p_environ, int fds[], int *p_success);
t_node **ft_get_semi_colon_child(char *cmd, t_env **copy_env);
t_ht *ft_create_table_bins(t_env **copy_env);
char **ft_get_args(char *cmd, t_env **copy_env);
char *ft_get_args_dollar(char *str, t_env **copy_env);
#endif