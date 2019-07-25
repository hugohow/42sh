/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_is_accessible.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:41:33 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/25 14:22:44 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_bin_is_accessible(char *path, int fds[])
{
	struct stat file_stat;

	ft_memset((void*)&file_stat, 0, sizeof(file_stat));
	if (stat(path, &file_stat))
	{
		lstat(path, &file_stat);
		if (S_ISLNK(file_stat.st_mode) && access(path, X_OK))
		{
			ft_dprintf(fds[2], "21sh:Too many symbolic links: %s\n", path);
			return (EXIT_FAIL);
		}
		ft_dprintf(fds[2], "21sh: No such file or directory: %s \n", path);
		return (EXIT_FAIL);
	}
	else if (access(path, X_OK))
	{
		ft_dprintf(fds[2], "21sh: permission denied : %s \n", path);
		return (EXIT_FAIL);
	}
	else if (S_ISDIR(file_stat.st_mode))
	{
		ft_dprintf(fds[2], "21sh: %s is not an executable\n", path);
		return (EXIT_UTILITY_NOT_EXEC);
	}
	return (0);
}
