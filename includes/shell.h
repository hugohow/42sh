/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 00:32:39 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/06 21:32:12 by hhow-cho         ###   ########.fr       */
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
#include <sys/ioctl.h>
#include <signal.h>
#include <sys/uio.h>
#include <term.h>
#include "libft.h"
#include "ht.h"
#include "ft_printf.h"


# define TYPE_BASE (1 << 0)
# define TYPE_CMD (1 << 1)
// # define TYPE_SEPARATOR (2 << 2)

# define BUF_SIZE 20
# define FLAG_CD_P (1 << 0)
# define FLAG_CD_L (1 << 1)
# define FLAG_ECHO_N (1 << 0)
# define FLAG_ENV_I (2 << 0)
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

# define FAIL_COPY_ENV "minishell: failed to copy env\n"

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
	int				nb_child;
    struct s_node **child;
}              t_node;

typedef struct s_env
{
    char *line;
}               t_env;

typedef struct	s_cmd
{
	t_list *head;
	int		last_key;
	unsigned long long		size;
	int		len;
	t_env	**copy_env;
}				t_cmd;

# define KEY_MUST_EXIT (2 << 1)
# define KEY_SUCCESS_EXIT (2 << 2)
# define KEY_COPY_ENV (2 << 3)
# define KEY_P_COPY_ENV (2 << 4)
# define KEY_PID (2 << 4)
# define KEY_CWD (2 << 5)
# define KEY_LAST_KEY (2 << 6)

typedef struct	s_vars
{
	t_env	**copy_env;
	t_env	**copy_env_special;
	struct termios old_config;
	struct termios new_config;
	int		must_exit;
	int		success_exit;
	int		pid;
	char	**argv_list;
	int 	argc;
	char	*cwd;
	t_ht 	*hash_table;
	int		last_key;
}				t_vars;

typedef int		(t_ft_apply)(t_cmd *);

typedef struct s_fts_apply
{
	int  key;
	t_ft_apply *fct;
}				t_fts_apply;

/*
** Two main functions
*/

int ft_interactive_exec(void);
int ft_non_interactive_exec(char **argv);
int ft_non_interactive_get_cmd(int fd, char **command, t_env **copy_env);

/*
** Functions for terminal interactions
*/

int ft_interactive_get_cmd(char **command, t_env **copy_env);
int ft_interactive_read_key(void);
void ft_interactive_prompt(void);
int ft_interactive_init();
void ft_interactive_exit();

t_node **get_child(t_node *node, char *cmd, t_env **copy_env);
t_node *create_node(long type, char *cmd, t_env **copy_env);
void    print_tree(t_node *node);

int is_separator(char *str);
int is_redirection(char *str);
int is_pipe(char *str);
void print_tokens(t_token **list);


void ft_cmd_exec(char *command, t_env ***p_copy_env, int fds[], int *p_success);

int					get_next_line(const int fd, char **line);


/*
** Functions related to environnement variables
*/

char *ft_env_get_line(t_env **cpy_environ, char *str);
char *ft_env_get_line_n(t_env **cpy_environ, char *str, size_t n);
char *ft_env_get_value(t_env **cpy_environ, char *prefix);
char *ft_env_get_value_n(t_env **cpy_environ, char *key, size_t n);

int ft_env_delete_line(char *prefix, t_env **cpy_environ);
int ft_env_change_line(char *prefix, char *line, t_env **cpy_environ);
char **ft_env_raw(t_env **cpy_environ);

t_env **ft_env_copy_raw(char **str, char **argv);
t_env **ft_env_copy_exit(t_env **env);
t_env **ft_env_add_default_pwd(t_env **copy);
t_env **ft_env_add_default_shlvl(t_env **copy);
t_env **ft_env_increment_shlvl(t_env **copy);

void ft_env_add(char *prefix, char *line, t_env ***p_environ);
int ft_env_cmp_prefix(char *prefix, char *line);
t_env **ft_env_deep_copy(t_env **str);
void ft_env_free(t_env ***p_cpy_environ);


/*
** Builtins
*/


int     ft_echo(char **argv, t_env **cpy_environ, int fds[]);
int     ft_cd(char **argv, t_env ***p_cpy_environ, int fds[]);
int		ft_cd_parse(int *p_argc, char ***p_argv);
int 	ft_cd_go_to(char *path, int fds[]);
int 	ft_cd_can_go_to(char *abs_path);
char *ft_cd_get_dest_path(char *element, t_env ***p_environ, int fds[]);
char *ft_cd_get_pwd_plus_element(t_env ***p_environ, char *element);
char 	*ft_cd_get_abs_path(t_env ***p_environ, char *element, int fds[]);
char *ft_cd_get_abs_path_cdpath(t_env ***p_environ, char *element, int fds[], char *cd_paths);
int 	ft_setenv(char **argv, t_env ***p_environ, int fds[]);
int 	ft_env(char **argv, t_env **cpy_environ, int fds[]);
int 	ft_env_parse(char ***p_argv, int fds[]);
char 	**ft_env_complete_env(char **argv, t_env ***p_copy_env, int flag, t_env **originial_env);
int 	ft_unsetenv(char **argv, t_env **cpy_environ, int fds[]);
int 	ft_exit(char **argv, t_env ***p_cpy_environ, int fds[]);




char *ft_env_autocomplete_cmd(char *begin, t_env **copy_env);
const char *ft_env_autocomplete_sugg_builtins(char *begin);
const char *ft_env_autocomplete_sugg_table(char *begin);

char *ft_path_trim(char *path);
char *ft_path_trim_free(char *abs_path);

void    print_normal(int fd);
void    ft_setenv_args(char *prefix, char *line, t_env ***p_environ);


size_t ft_list_size(char **list);
void ft_list_free(char ***p_list);
void ft_list_free_n(char ***p_list, size_t len);

int ft_is_path(char *cmd);
void ft_print_env(t_env **str, int fds[]);
void print_cmd(char *cmd);
void add_to_stdout(char **p_cmd, int c, int *index);
void delete_n_lines(int n);
int count_nb_line(char *cmd);

int ft_exe_path(char **argv, t_env **cpy_environ, int fds[]);
int ft_ask_command(int fd, char **command);


t_node *ft_syntax_tree_create(char *cmd, t_env **copy_env);
void ft_syntax_tree_free(t_node **root);


int ft_exe_bin(t_node *node, t_env ***p_environ, int fds[]);
void    ft_syntax_tree_execute(t_node *node, t_env ***p_environ, int fds[], int *p_success);
t_node **ft_get_semi_colon_child(t_node *node, char *cmd, t_env **copy_env);
t_ht *ft_bins_table_create(char *line);
t_ht * ft_bins_table_get(void);
char **ft_args_get(char *cmd, t_env **copy_env, int *p_result_parsing);
char *ft_args_dollar_get(char *str, t_env **copy_env, int *p_result_parsing);
char *ft_args_dollar_replace_expansion(char *str, int i, int ret, t_env **copy_env);
int ft_args_dollar_is_valid(char *str);

int ft_bin_is_accessible(char *path, int fds[]);

char *ft_args_tilde_get(char *str, t_env **copy_env);
int	ft_isatty(int fd);
char *ft_node_join(t_list *head, unsigned long long size);
char			**ft_str_separate(char const *str, char c);
char *ft_strjoin_(char *str1, char *str2, char *str3);
char *ft_strjoin_free_first(char *prefix, char *to_free);
char *ft_strjoin_free_second(char *prefix, char *to_free);

int ft_apply_key(t_cmd *cmd);

int ft_apply_tab(t_cmd *cmd);
int ft_apply_ctrl_c(t_cmd *cmd);
int ft_apply_ctrl_d(t_cmd *cmd);
int ft_apply_del(t_cmd *cmd);
int ft_apply_printable(t_cmd *cmd);
int ft_apply_enter(t_cmd *cmd);

t_vars     *ft_vars_get(void);
void     *ft_vars_get_value(long key);
int	ft_vars_init(int argc, char **argv);
t_env     **ft_vars_get_copy_env(void);
t_env     ***ft_vars_get_p_copy_env(void);
void ft_vars_free(void);

const char			*ft_errors_signal_get(int signal);
const char			*ft_errors_stop_get(int sig);
#endif