/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 13:33:15 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/13 16:23:21 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*ft_env_get_cmd(char **argv)
{
	int		i;
	int		len;
	char	*cmd;

	i = 0;
	len = 0;
	while (argv[i])
	{
		len += ft_strlen(argv[i]) + 2;
		i++;
	}
	if (!(cmd = (char *)ft_memalloc(len * sizeof(char))))
		return (NULL);
	i = 0;
	while (argv[i])
	{
		cmd = ft_strcat(cmd, argv[i]);
		cmd = ft_strcat(cmd, " ");
		i++;
	}
	return (cmd);
}

static void ft_env_exe_path(char **argv, t_env ***p_copy_env, t_ht **p_hash, int fds[])
{
    int status;
	char *cmd;

	cmd = ft_env_get_cmd(argv);
	if (*p_hash)
	{
		ft_cmd_exec(cmd, p_copy_env, p_hash, fds);
		ft_ht_free(p_hash);
	}
	else
		ft_cmd_exec(cmd, p_copy_env, NULL, fds);
	ft_env_free(p_copy_env);
	ft_memdel((void **)&(p_hash));
	status = *((int *)ft_vars_get_value(KEY_SUCCESS_EXIT));
	ft_vars_free();
	exit(status);
}

int ft_env_cmd_exec(char **argv, t_ht **p_hash, t_env ***p_copy_env, int fds[])
{
	int i;
	pid_t pid;
	int waitstatus;
	int w;

	i = 0;
	if (*argv)
	{
		if ((ft_find_bin(*argv, p_hash)) < 0)
		{
			ft_dprintf(fds[2], \
				"minishell env : command not found: %s\n", *argv);
			i = EXIT_UTILITY_NOT_FOUND;
		}
		else
		{
			pid = fork();
			if (pid < 0)
			{
				ft_putstr_fd("erreur pid", fds[2]);
				return (1);
			}
			if (pid == 0)
				ft_env_exe_path(argv, p_copy_env, p_hash, fds);
			else
			{
				w = waitpid(pid, &waitstatus, WUNTRACED | WCONTINUED);
				if (w == -1)
					return (EXIT_FAILURE);
				if (WIFSIGNALED(waitstatus))
					ft_dprintf(fds[2], "%s\n", \
						ft_errors_signal_get(WTERMSIG(waitstatus)));
			}
			i = WEXITSTATUS(waitstatus);
		}
	}
	else
		ft_print_env(*p_copy_env, fds);
	return (i);
}
