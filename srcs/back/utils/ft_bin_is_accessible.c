/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_is_accessible.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:41:33 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/06 19:41:51 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_bin_is_accessible(char *path, int fds[])
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