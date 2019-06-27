/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_get_abs_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 22:25:10 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/27 22:35:25 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *ft_cd_get_abs_path(t_env ***p_environ, char *element, int fds[])
{
    char *curpath;
	char *cd_path;
	char *pwd;

    if (ft_strncmp("/", element, 1) == 0)
        return (ft_path_trim(element));
    if (ft_strcmp(".", element) == 0 || ft_strcmp("..", element) == 0)
	{
		pwd = ft_env_get_value(*p_environ, "PWD");
		if (pwd == NULL)
			pwd = getcwd(NULL, 0);
		curpath = ft_strjoin(pwd, "/");
		curpath = ft_strjoin(curpath, element);
		curpath = ft_path_trim_free(curpath);
		return (curpath);
	}
	cd_path = ft_env_get_value(*p_environ, "CDPATH");
	if (cd_path == NULL)
	{
		pwd = ft_env_get_value(*p_environ, "PWD");
		if (pwd == NULL)
			pwd = getcwd(NULL, 0);
		curpath = ft_strjoin(pwd, "/");
		curpath = ft_strjoin(curpath, element);
		curpath = ft_path_trim_free(curpath);
		return (curpath);
	}
	else
	{
		char **list;

		list = ft_str_separate(cd_path, ':');

		if (ft_strlen(list[0]) == 0)
		{
			curpath = ft_strjoin("./", element);
			if (ft_cd_can_go_to(curpath) == 1)
			{
				pwd = ft_env_get_value(*p_environ, "PWD");
				if (pwd == NULL)
					pwd = getcwd(NULL, 0);
				curpath = ft_strjoin(pwd, curpath + 1);
				curpath = ft_path_trim_free(curpath);
				return (curpath);
			}
			curpath = NULL;
		}

		int i;

		i = 0;
		while (list && list[i])
		{
			if (ft_strlen(list[i]) == 0)
			{
				i++;
				continue ;
			}
			if (ft_strncmp("/", list[i], 1) == 0)
			{
				curpath = ft_strjoin(list[i], "/");
				curpath = ft_strjoin(curpath, element);
				curpath = ft_path_trim_free(curpath);
				if (ft_cd_can_go_to(curpath) == 1)
				{
					ft_putstr_fd(curpath, fds[1]);
					ft_putstr_fd("\n", fds[1]);
					return (curpath);
				}
				curpath = NULL;
			}
			pwd = ft_env_get_value(*p_environ, "PWD");
			if (pwd == NULL)
				pwd = getcwd(NULL, 0);
			curpath = ft_strjoin(pwd, "/");
			curpath = ft_strjoin(curpath, list[i]);
			curpath = ft_strjoin(curpath, "/");
			curpath = ft_strjoin(curpath, element);
			curpath = ft_path_trim(curpath);
			if (ft_cd_can_go_to(curpath) == 1)
			{
				ft_putstr_fd(curpath, fds[1]);
				ft_putstr_fd("\n", fds[1]);
				return (curpath);
			}
			curpath = NULL;
			i++;
		}
	}
	return (NULL);
}