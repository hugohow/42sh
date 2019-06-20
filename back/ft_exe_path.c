/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 14:28:12 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 16:18:35 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

int ft_exe_path(char *path, char **argv, t_env **cpy_environ, int fds[])
{
    pid_t pid;
    struct stat fileStat;
    int waitstatus;
    int i;
    i = 0;

    if (stat(path, &fileStat) < 0)
    {
        ft_putstr_fd("Too many symbolic links\n", fds[2]);
        return (-1);
    }
    if (lstat(path, &fileStat) < 0)
    {
        ft_putstr_fd("Command not found\n", fds[2]);
        return (-1);
    }
    if (access(path, X_OK) == -1)
    {
        ft_putstr_fd("Permission denied\n", fds[2]);
        return (-1);
    }
    pid = fork();
    if (pid < 0) 
    {
        ft_putstr_fd("Failed to fork process 1\n", fds[2]);
        exit(1);
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
				ft_putstr_fd("erreure\n", fds[2]);
		}
		ft_memdel((void **)(cpy_env_raw));
        exit(0);
    }
	else
	{
    // if (fd0 != 0)
    //     close(fd0);
    // if (fd1 != 1)
    //     close(fd1);
    // do {
        int w;
        w = waitpid(pid, &waitstatus, WUNTRACED | WCONTINUED);
        if (w == -1) {
            // perror("waitpid");
            exit(EXIT_FAILURE);
        }

    //     if (WIFEXITED(waitstatus)) {
    //         printf("terminé, code=%d\n", WEXITSTATUS(waitstatus));
    //     } else if (WIFSIGNALED(waitstatus)) {
    //         printf("tué par le signal %d\n", WTERMSIG(waitstatus));
    //     } else if (WIFSTOPPED(waitstatus)) {
    //         printf("arrêté par le signal %d\n", WSTOPSIG(waitstatus));
    //     } else if (WIFCONTINUED(waitstatus)) {
    //         printf("relancé\n");
    //     }
    // } while (!WIFEXITED(waitstatus) && !WIFSIGNALED(waitstatus));
	}
	// parent
    i = WEXITSTATUS(waitstatus);

    return (i);
}