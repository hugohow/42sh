/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 13:33:15 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/13 19:51:49 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// static char	*ft_env_get_cmd(char **argv)
// {
// 	int		i;
// 	int		len;
// 	char	*cmd;

// 	i = 0;
// 	len = 0;
// 	while (argv[i])
// 	{
// 		len += ft_strlen(argv[i]) + 2;
// 		i++;
// 	}
// 	if (!(cmd = (char *)ft_memalloc(len * sizeof(char))))
// 		return (NULL);
// 	i = 0;
// 	while (argv[i])
// 	{
// 		cmd = ft_strcat(cmd, argv[i]);
// 		cmd = ft_strcat(cmd, " ");
// 		i++;
// 	}
// 	return (cmd);
// }

// static void	child_exec(char *path, char **argv, t_env **cpy_environ, int fds[])
// {
// 	char **cpy_env_raw;

// 	cpy_env_raw = ft_env_raw(cpy_environ);
// 	if (cpy_env_raw)
// 	{
// 		if (execve(path, argv, cpy_env_raw) < 0)
// 			ft_putstr_fd("erreur\n", fds[2]);
// 		ft_memdel((void **)(cpy_env_raw));
// 	}
// }

// static void	ft_env_exe_path(char **argv, t_env ***p_copy_env,\
// 	t_ht **p_hash, int fds[])
// {
// 	char	*cmd;

// 	cmd = ft_env_get_cmd(argv);
// 	if (*p_hash)
// 		ft_cmd_exec(cmd, p_copy_env, p_hash, fds);
// 	else
// 		ft_cmd_exec(cmd, p_copy_env, NULL, fds);
// 	printf("exit value : %d\n", *((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)));
// 	child_exec("/usr/bin/true", (char *[15]){"/usr/bin/true"}\
// 		, *p_copy_env, fds);
// 	exit(*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)));
// }

// static int	ft_fork_and_exec(char **argv, t_env ***p_copy_env,\
// 	t_ht **p_hash, int fds[])
// {
// 	pid_t	pid;
// 	int		i;
// 	int		waitstatus;
// 	int		w;

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		ft_putstr_fd("erreur pid", fds[2]);
// 		return (1);
// 	}
// 	if (pid == 0)
// 		ft_env_exe_path(argv, p_copy_env, p_hash, fds);
// 	else
// 	{
// 		w = waitpid(pid, &waitstatus, WUNTRACED | WCONTINUED);
// 		if (w == -1)
// 			return (EXIT_FAILURE);
// 		if (WIFSIGNALED(waitstatus))
// 			ft_dprintf(fds[2], "%s\n", \
// 				ft_errors_signal_get(WTERMSIG(waitstatus)));
// 	}
// 	i = WEXITSTATUS(waitstatus);
// 	return (i);
// }

int			ft_env_cmd_exec(char **argv, \
	t_ht **p_hash, t_env ***p_copy_env, int fds[])
{
	int		i;

	i = 0;
	if (*argv)
	{

	if (ft_is_path(node->args[0]) == 1)
		result_cmd = ft_exe_path(node->args, *p_env, fds);
	else
		result_cmd = ft_search_and_exe_bin(node, *p_env, p_hash, fds);


		if (p_hash_table \
		&& *p_hash_table \
		&& (value = ft_ht_get(*p_hash_table, cmd_exec)) \
		&& value->datum)

// il faut que ce soit soit un path ou exec comme un binaire


		if ((ft_find_bin(*argv, p_hash)) < 0)
		{
			ft_dprintf(fds[2], \
				"minishell env : command not found: %s\n", *argv);
			i = EXIT_UTILITY_NOT_FOUND;
		}
		else
			i = ft_exe_path(argv, *p_copy_env, fds);
	}
	else
		ft_print_env(*p_copy_env, fds);
	return (i);
}
