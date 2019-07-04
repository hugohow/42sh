/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 14:28:12 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/04 19:01:14 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

static int check_if_bin(char *path, int fds[])
{
	struct stat fileStat;

	ft_memset((void*)&fileStat, 0, sizeof(fileStat));
	if (stat(path, &fileStat))
	{
		lstat(path, &fileStat);
		if (S_ISLNK(fileStat.st_mode) && access(path, X_OK))
		{
			ft_dprintf(fds[2], "Too many symbolic links: %s \n", path);
			return (EXIT_FAIL);
		}
		ft_dprintf(fds[2], "No such file or directory: %s \n", path);
		return (EXIT_FAIL);
	}
	else if (access(path, X_OK))
	{
		ft_dprintf(fds[2], "permission denied : %s \n", path);
		return (EXIT_FAIL);
	}
	return (0);
}

int ft_exe_path(char **argv, t_env **cpy_environ, int fds[])
{
    pid_t pid;
    int waitstatus;
    int i;
	char *path;

	path = argv[0];
	if ((i = check_if_bin(path, fds)) != 0)
		return (i);
    pid = fork();
    if (pid < 0) 
    {
        ft_dprintf(fds[2], "Failed to fork process 1: %s \n", path);
        return (EXIT_FAILURE);
    }
    if (pid == 0)
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
	else
	{
        int w;
        w = waitpid(pid, &waitstatus, WUNTRACED | WCONTINUED);
        if (w == -1)
		{
            // perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(waitstatus)) {
            // printf("terminé, code=%d\n", WEXITSTATUS(waitstatus));
        } else if (WIFSIGNALED(waitstatus)) {
            ft_printf("%s\n", ft_errors_signal_get(WTERMSIG(waitstatus)));
        } else if (WIFSTOPPED(waitstatus)) {
            ft_printf("%s\n", ft_errors_stop_get(WTERMSIG(waitstatus)));
        } else if (WIFCONTINUED(waitstatus)) {
            // ft_printf("relancé\n");
        }
	}
    i = WEXITSTATUS(waitstatus);

    return (i);
}