/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 00:32:39 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/09 00:46:39 by hhow-cho         ###   ########.fr       */
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

extern char **environ;

int     get_next_line(const int fd, char **line);
int     ft_printf(const char* format, ...);


char *get_line_env(char *str, char ***p_environ);
void    print_normal(int fd);
int     change_line_env(char *key, char *line, char ***p_environ);
void    ft_setenv_args(char *prefix, char *line, char ***p_environ);
int ft_execute_path(char *path, char **argv, char ***p_environ, int fd0, int fd1, int fd2);
int     ft_echo(int argc, char **argv, char ***p_environ, int fd0, int fd1, int fd2);
int     ft_cd(int argc, char **argv, char ***p_environ);
int     ft_setenv(int argc, char **argv, char ***p_environ);
int ft_env(int argc, char **argv, char ***p_environ, struct termios *p_orig_termios);
int ft_unsetenv(int argc, char **argv, char ***p_environ);
void ft_print_env(char **str);
int delete_line_env(char *key, char ***p_environ);
char *get_line_env(char *str, char ***p_environ);
void    ft_exit_terminal(struct termios *orig_termios);
int     ft_init_terminal(struct termios *orig_termios, struct termios *new_termios);
int     ft_read_key();
void print_cmd(char *cmd);
void add_to_stdout(char **p_cmd, int c, int *index);
void delete_n_lines(int n);
int count_nb_line(char *cmd);
int prepare_command(char *cmd, char ***copy_env, int prev_res, struct termios *p_orig_termios);
int ft_execute_path(char *path, char **argv, char ***p_environ, int fd0, int fd1, int fd2);
int ft_ask_command(int fd, char **command, struct termios *p_orig_termios);
void ft_exit(char *cmd, int success, struct termios *p_orig_termios);
char **copy_environ(char **str);
char **get_paths(char **copy_env);
int execute_command(char *cmd, char **paths, char ***p_environ, struct termios *p_orig_termios, int fd0, int fd1, int fd2);


#endif