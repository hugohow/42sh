/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 00:32:39 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/09 03:04:51 by hhow-cho         ###   ########.fr       */
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
#include "libft.h"

# define TYPE_BASE (2 << 0)
# define TYPE_CMD (2 << 1)
# define TYPE_SEPARATOR (2 << 1)

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
    // pour la redirection
    int nb_pipe;
    int fd_origin;
    char *file_name;
    struct s_node **child;
}              t_node;


t_node **get_child(char *cmd);
t_node *create_node(long type, char *cmd);
void    print_tree(t_node *node);

int is_separator(char *str);
int is_redirection(char *str);
int is_pipe(char *str);
void print_tokens(t_token **list);


int     get_next_line(const int fd, char **line);
int     ft_printf(const char* format, ...);


char *get_line_env(char *str, char ***p_environ);
void    print_normal(int fd);
int     change_line_env(char *key, char *line, char ***p_environ);
void    ft_setenv_args(char *prefix, char *line, char ***p_environ);
int     ft_echo(int argc, char **argv, char ***p_environ, int fd0, int fd1, int fd2);
int     ft_cd(int argc, char **argv, char ***p_environ);
int     ft_setenv(int argc, char **argv, char ***p_environ);
int ft_env(int argc, char **argv, char ***p_environ);
int ft_unsetenv(int argc, char **argv, char ***p_environ);
void ft_print_env(char **str);
int delete_line_env(char *key, char ***p_environ);
char *get_line_env(char *str, char ***p_environ);
void    ft_exit_terminal(void);
int     ft_init_terminal(struct termios *orig_termios, struct termios *new_termios);
int     ft_read_key();
void print_cmd(char *cmd);
void add_to_stdout(char **p_cmd, int c, int *index);
void delete_n_lines(int n);
int count_nb_line(char *cmd);
int ft_parse_cmd(char *cmd, char ***copy_env, int prev_res);
int ft_exe_path(char *path, char **argv, char ***p_environ, int fd0, int fd1, int fd2);
int ft_ask_command(int fd, char **command);
void ft_exit(char *cmd, int success);
char **copy_environ(char **str);
char **get_paths(char **copy_env);
int ft_exe_bin(char *cmd, char **paths, char ***p_environ, int fd0, int fd1, int fd2);
int is_exit(char *cmd);
int ft_get_cmd(int fd, char **command);
void    execute_tree(t_node *node, char **paths, char ***p_environ, int fd0, int fd1, int fd2, int *p_success);
t_node **ft_get_semi_colon_child(char *cmd);
#endif