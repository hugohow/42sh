/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_go_to.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:45:53 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/13 12:53:27 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_cd_can_go_to(char *abs_path)
{
	struct stat	file_stat;

	ft_memset((void*)&file_stat, 0, sizeof(file_stat));
	if (stat(abs_path, &file_stat))
		return (-1);
	else if (!S_ISDIR(file_stat.st_mode) && !S_ISLNK(file_stat.st_mode))
		return (-1);
	else if (access(abs_path, X_OK))
		return (-1);
	return (1);
}

int		ft_cd_can_go_to_message(char *abs_path, char *element, int fds[])
{
	struct stat	file_stat;

	ft_memset((void*)&file_stat, 0, sizeof(file_stat));
	if (abs_path == NULL)
		ft_dprintf(fds[2], "cd: No such file or directory: %s\n", element);
	else if (stat(abs_path, &file_stat))
	{
		lstat(abs_path, &file_stat);
		if (S_ISLNK(file_stat.st_mode) && access(abs_path, X_OK))
			ft_dprintf(fds[2], "cd: Too many symbolic links: %s\n", abs_path);
		else
			ft_dprintf(fds[2], "cd: No such file or directory: %s\n", abs_path);
	}
	else if (!S_ISDIR(file_stat.st_mode) && !S_ISLNK(file_stat.st_mode))
		ft_dprintf(fds[2], "cd: Not a directory: %s\n", abs_path);
	else if (access(abs_path, X_OK))
		ft_dprintf(fds[2], "cd: Permission denied: %s\n", abs_path);
	else
		return (1);
	return (-1);
}

int		ft_cd_go_to(char *path, char *element, int fds[])
{
	struct stat	file_stat;

	ft_memset((void*)&file_stat, 0, sizeof(file_stat));
	if (path == NULL)
		ft_dprintf(fds[2], "cd: No such file or directory: %s\n", element);
	if (stat(path, &file_stat))
	{
		lstat(path, &file_stat);
		if (S_ISLNK(file_stat.st_mode) && access(path, X_OK))
			ft_dprintf(fds[2], "cd: Too many symbolic links: %s\n", path);
		else
			ft_dprintf(fds[2], "cd: No such file or directory: %s\n", path);
	}
	else if (!S_ISDIR(file_stat.st_mode) && !S_ISLNK(file_stat.st_mode))
		ft_dprintf(fds[2], "cd: Not a directory: %s\n", path);
	else if (access(path, X_OK))
		ft_dprintf(fds[2], "cd: Permission denied: %s\n", path);
	else
		return (chdir(path));
	return (EXIT_FAIL);
}
