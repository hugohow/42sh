/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_go_to.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:45:53 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/06 22:21:24 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_cd_can_go_to(char *abs_path)
{
    struct stat fileStat;

	ft_memset((void*)&fileStat, 0, sizeof(fileStat));
	if (stat(abs_path, &fileStat))
		return (-1);
	else if (!S_ISDIR(fileStat.st_mode) && !S_ISLNK(fileStat.st_mode))
		return (-1);
	else if (access(abs_path, X_OK))
		return (-1);
    return (1);
}


int ft_cd_go_to(char *path, int fds[])
{
    struct stat fileStat;

	ft_memset((void*)&fileStat, 0, sizeof(fileStat));
	if (stat(path, &fileStat))
	{
		lstat(path, &fileStat);
		if (S_ISLNK(fileStat.st_mode) && access(path, X_OK))
		{
			ft_dprintf(fds[2], "minishell: cd: Too many symbolic links: %s\n", path);
			return (EXIT_FAIL);
		}
		ft_dprintf(fds[2], "minishell: cd: No such file or directory: %s\n", path);
		return (EXIT_FAIL);
	}
	else if (!S_ISDIR(fileStat.st_mode) && !S_ISLNK(fileStat.st_mode))
	{
		ft_dprintf(fds[2], "minishell: cd: Not a directory: %s\n", path);
		return (EXIT_FAIL);
	}
	else if (access(path, X_OK))
	{
		ft_dprintf(fds[2], "minishell: cd: Permission denied: %s\n", path);
		return (EXIT_FAIL);
	}
    return (chdir(path));
}