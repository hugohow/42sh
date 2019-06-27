/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_go_to.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:45:53 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/27 22:42:51 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_cd_can_go_to(char *abs_path)
{
    struct stat fileStat;

	if (stat(abs_path, &fileStat))
		return (-1);
	else if (!S_ISDIR(fileStat.st_mode) && !S_ISLNK(fileStat.st_mode))
		return (-1);
	else if (access(abs_path, X_OK))
		return (-1);
    return (1);
}


int ft_cd_go_to(char *curpath, int fds[])
{
    struct stat fileStat;

	if (stat(curpath, &fileStat))
	{
		lstat(curpath, &fileStat);
		if (S_ISLNK(fileStat.st_mode) && access(curpath, X_OK))
		{
			ft_dprintf(fds[2], "minishell: cd: Too many symbolic links: %s\n", curpath);
			return (EXIT_FAIL);
		}
		ft_dprintf(fds[2], "minishell: cd: No such file or directory: %s\n", curpath);
		return (EXIT_FAIL);
	}
	else if (!S_ISDIR(fileStat.st_mode) && !S_ISLNK(fileStat.st_mode))
	{
		ft_dprintf(fds[2], "minishell: cd: Not a directory: %s\n", curpath);
		return (EXIT_FAIL);
	}
	else if (access(curpath, X_OK))
	{
		ft_dprintf(fds[2], "minishell: cd: Permission denied: %s\n", curpath);
		return (EXIT_FAIL);
	}
    return (chdir(curpath));
}