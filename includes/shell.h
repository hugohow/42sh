/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 00:32:39 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/13 13:35:17 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <sys/uio.h>
# include <term.h>
# include <pwd.h>
# include "libft.h"
# include "ht.h"
# include "ft_printf.h"
# include "shell_struct.h"
# define KEY_MUST_EXIT (2 << 1)
# define KEY_SUCCESS_EXIT (2 << 2)
# define KEY_COPY_ENV (2 << 3)
# define KEY_P_COPY_ENV (2 << 4)
# define KEY_PID (2 << 4)
# define KEY_CWD (2 << 5)
# define KEY_LAST_KEY (2 << 6)
# define TYPE_BASE (1 << 0)
# define TYPE_CMD (1 << 1)
# define BUF_SIZE 20
# define FLAG_CD_P (1 << 0)
# define FLAG_CD_L (1 << 1)
# define FLAG_ECHO_N (1 << 0)
# define FLAG_ENV_I (2 << 0)
# define EXIT_SUCCESS 0
# define EXIT_FAIL 1
# define EXIT_UTILITY_NOT_FOUND 127
# define EXIT_UTILITY_NOT_EXEC 126
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
# define DEFAULT_PATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

/*
** main functions
*/

int			ft_interactive_exec(void);
int			ft_non_interactive_exec(char **argv);
int			ft_non_interactive_get_cmd(int fd, char **cmd);
void		ft_cmd_exec(char *cmd, t_env ***p_env, t_ht **p_tab, int fds[]);

/*
** Functions for terminal interactions
*/

int			ft_interactive_get_cmd(char **command);
int			ft_interactive_read_key(void);
void		ft_interactive_prompt(void);
int			ft_interactive_init();
void		ft_interactive_exit();
int			ft_cmd_init(void);

/*
** Functions for parsing
*/

t_node		**get_child(t_node *node, char *cmd, t_env **copy_env);
t_node		*create_node(long type, char *cmd, t_env **copy_env);
t_ht		*ft_bins_table_create(char *line);
t_ht		**ft_p_bins_table_get(void);
char		**ft_args_get(char *cmd, t_env **copy_env, int *p_result_parsing);
char		*ft_args_get_first(char *cmd, t_env **copy_env);
char		*ft_args_dollar_get(char *str, t_env **copy_env, \
	int *p_result_parsing);
char		*ft_args_dollar_replace_expansion(char *str, int i,\
	int ret, t_env **c_env);
int			ft_args_dollar_is_valid(char *str);
char		*ft_args_tilde_get(char *str, t_env **copy_env);
char		*ft_replace_by_home_login(char *str, int i, char *login);
char		*ft_replace_by_home(char *str, int i, t_env **copy_env);
char		*ft_replace_by_oldpwd(char *str, int i, t_env **copy_env);
char		*ft_replace_by_pwd(char *str, int i, t_env **copy_env);
t_node		*ft_syntax_tree_create(char *cmd, t_env **copy_env);
void		ft_syntax_tree_free(t_node **root);
t_node		**ft_get_semi_colon_child(t_node *node, char *cmd, \
	t_env **copy_env);
char		*ft_cmd_exec_get(char *cmd);
char		**ft_args_split(char *cmd);
int			ft_str_brackets_is_valid(char *str, size_t len);

/*
** Functions related to environnement variables
*/

char		*ft_env_get_line(t_env **cpy_environ, char *str);
char		*ft_env_get_line_n(t_env **cpy_environ, char *str, size_t n);
char		*ft_env_get_value(t_env **cpy_environ, char *prefix);
char		*ft_env_get_value_n(t_env **cpy_environ, char *key, size_t n);
int			ft_env_delete_line(char *prefix, t_env **cpy_environ);
int			ft_env_change_line(char *prefix, char *line, t_env **cpy_environ);
char		**ft_env_raw(t_env **cpy_environ);
t_env		**ft_env_copy_raw(char **str, char **argv);
t_env		**ft_env_copy_exit(t_env **env);
t_env		**ft_env_add_default_pwd(t_env **copy);
t_env		**ft_env_add_default_shlvl(t_env **copy);
t_env		**ft_env_increment_shlvl(t_env **copy);
void		ft_env_add(char *prefix, char *line, t_env ***p_env);
int			ft_env_cmp_prefix(char *prefix, char *line);
t_env		**ft_env_deep_copy(t_env **str);
void		ft_env_free(t_env ***p_cpy_environ);

/*
** Builtins
*/

int			ft_echo(char **argv, t_env **cpy_environ, int fds[]);
int			ft_cd(char **argv, t_env ***p_cpy_environ, int fds[]);
int			ft_cd_parse(int *p_argc, char ***p_argv);
int			ft_cd_go_to(char *path, char *element, int fds[]);
int			ft_cd_can_go_to(char *abs_path);
int			ft_cd_can_go_to_message(char *abs_path, char *element, int fds[]);
int			ft_cd_change_env(char *new_pwd_line, t_env ***p_env);
char		*ft_cd_get_dest_path(char *element, t_env ***p_env, \
	long long flag, int fds[]);
char		*ft_cd_get_pwd_plus_element(t_env ***p_env, char *element);
char		*ft_cd_get_abs_path_cdpath(t_env ***p_env, char *element,\
	int fds[], char *cd_paths);
char		*ft_cd_get_path_home(t_env ***p_environ, int fds[]);
char		*ft_cd_get_absolute_path(char *element, int fds[]);
char		*ft_cd_get_old_path(t_env ***p_environ, int fds[]);
char		*ft_cd_get_path_cdpath(char *element, t_env ***p_env, int fds[]);
int			ft_setenv(char **argv, t_env ***p_env, t_ht **p_table_bins,\
	int fds[]);
int			ft_env(char **argv, t_env **cpy_environ, int fds[]);
int			ft_env_cmd_exec(char **argv, t_ht **p_hash, t_env ***p_copy_env, int fds[]);
int			ft_env_parse(char ***p_argv, int fds[]);
char		**ft_env_complete_env(char **argv, t_env ***p_copy_env, t_ht **p_hash);
int			ft_unsetenv(char **argv, t_env **cpy_environ,\
	t_ht **p_table_bins, int fds[]);
int			ft_exit(char **argv, t_env ***p_cpy_environ, int fds[]);

/*
** Exec fcts
*/

int			ft_exe_path(char **argv, t_env **cpy_environ, int fds[]);
int			ft_find_bin(char *cmd_exec, t_ht **p_hash);
int			ft_exe_bin(t_node *node, t_env ***p_env, t_ht **p_table_bins,\
	int fds[]);
int			ft_syntax_tree_execute(t_node *node, t_env ***p_env,\
	t_ht **p_table_bins, int fds[]);

/*
** Utils
*/

char		*ft_path_trim(char *path);
char		*ft_path_trim_free(char *abs_path);
size_t		ft_list_size(char **list);
void		ft_list_free(char ***p_list);
void		ft_list_free_n(char ***p_list, size_t len);
int			ft_is_path(char *cmd);
void		ft_print_env(t_env **str, int fds[]);
int			ft_bin_is_accessible(char *path, int fds[]);
int			ft_isatty(int fd);
char		*ft_node_join(t_list *head, unsigned long long size);
char		**ft_str_separate(char const *str, char c);
char		*ft_strjoin_(char *str1, char *str2, char *str3);
char		*ft_strjoin_free_first(char *prefix, char *to_free);
char		*ft_strjoin_free_second(char *prefix, char *to_free);

/*
** Effect on press key fcts
*/

int			ft_apply_key(t_cmd *cmd);
int			ft_apply_tab(t_cmd *cmd);
int			ft_apply_ctrl_c(t_cmd *cmd);
int			ft_apply_ctrl_d(t_cmd *cmd);
int			ft_apply_del(t_cmd *cmd);
int			ft_apply_printable(t_cmd *cmd);
int			ft_apply_enter(t_cmd *cmd);

/*
** Global variables fcts
*/

t_vars		*ft_vars_get(void);
void		*ft_vars_get_value(long key);
int			ft_vars_init(int argc, char **argv, char *envp[]);
t_env		**ft_vars_get_copy_env(void);
t_env		***ft_vars_get_p_copy_env(void);
void		ft_vars_free(void);

/*
** Error messages
*/

const char	*ft_errors_signal_get(int signal);
const char	*ft_errors_stop_get(int sig);

/*
** Autocomplete functions
*/

char		*ft_env_autocomplete_cmd(char *begin);
const char	*ft_env_autocomplete_sugg_builtins(char *begin);
const char	*ft_env_autocomplete_sugg_table(char *begin);

#endif
