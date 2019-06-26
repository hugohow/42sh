/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 14:28:12 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/27 00:57:19 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

int ft_exe_path(char **argv, t_env **cpy_environ, int fds[])
{
    pid_t pid;
    struct stat fileStat;
    int waitstatus;
    int i;
	char *path;
    i = 0;

	path = argv[0];
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
    pid = fork();
    if (pid < 0) 
    {
        ft_dprintf(fds[2], "Failed to fork process 1: %s \n", path);
        return (EXIT_FAILURE);
    }
    if (pid == 0)
    {
    //     if (fd0 != 0)
    //     {
    //         dup2(fd0, STDIN_FILENO);    
    //         close(fd0);
    //     }
    //     if (fd1 != 1)
    //     {
    //         dup2(fd1, STDOUT_FILENO);
    //         close(fd1);
    //     }
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
    // if (fd0 != 0)
    //     close(fd0);
    // if (fd1 != 1)
    //     close(fd1);
    // while (!WIFEXITED(waitstatus) && !WIFSIGNALED(waitstatus))
	// {
        int w;
        w = waitpid(pid, &waitstatus, WUNTRACED | WCONTINUED);
        if (w == -1) {
            // perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(waitstatus)) {
            // printf("terminé, code=%d\n", WEXITSTATUS(waitstatus));
        } else if (WIFSIGNALED(waitstatus)) {
            ft_printf("tué par le signal %d\n", WTERMSIG(waitstatus));
        } else if (WIFSTOPPED(waitstatus)) {
            ft_printf("arrêté par le signal %d\n", WSTOPSIG(waitstatus));
        } else if (WIFCONTINUED(waitstatus)) {
            ft_printf("relancé\n");
        }
	// }
	}
	// parent
    i = WEXITSTATUS(waitstatus);

    return (i);
}