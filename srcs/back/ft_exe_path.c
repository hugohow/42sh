/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:39:35 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/13 16:08:47 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	child_exec(char *path, char **argv, t_env **cpy_environ, int fds[])
{
	char **cpy_env_raw;

	cpy_env_raw = ft_env_raw(cpy_environ);
	if (cpy_env_raw)
	{
		if (execve(path, argv, cpy_env_raw) < 0)
			ft_putstr_fd("erreur\n", fds[2]);
		ft_memdel((void **)(cpy_env_raw));
	}
	exit(0);
}

int			ft_exe_path(char **argv, t_env **cpy_environ, int fds[])
{
	pid_t	pid;
	int		waitstatus;
	int		i;
	int		w;

	if ((i = ft_bin_is_accessible(argv[0], fds)) != 0)
		return (i);
	if ((pid = fork()) < 0)
	{
		ft_dprintf(fds[2], "Failed to fork process 1: %s \n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (pid == 0)
		child_exec(argv[0], argv, cpy_environ, fds);
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
	return (i);
}
