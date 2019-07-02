/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_get_abs_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 22:25:10 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/02 02:41:07 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char*get_pwd_plus_element(t_env ***p_environ, char *element)
{
    char *curpath;
	char *pwd;

	pwd = ft_strdup(ft_env_get_value(*p_environ, "PWD"));
	if (pwd == NULL)
		pwd = getcwd(NULL, 0);
	curpath = ft_strjoin_(pwd, "/", element);
	curpath = ft_path_trim_free(curpath);
	ft_memdel((void **)&pwd);
	return (curpath);
}

char *ft_cd_get_abs_path(t_env ***p_environ, char *element, int fds[])
{
    char *curpath;
	char *cd_path;
	// char *pwd;

    if (ft_strncmp("/", element, 1) == 0)
        return (ft_path_trim(element));
    if (ft_strcmp(".", element) == 0 || ft_strcmp("..", element) == 0)
		return (get_pwd_plus_element(p_environ, element));
	cd_path = ft_env_get_value(*p_environ, "CDPATH");
	if (cd_path == NULL)
		return (get_pwd_plus_element(p_environ, element));
	else
	{
		char **list;

		list = ft_str_separate(cd_path, ':');

		if (ft_strlen(list[0]) == 0)
		{
			curpath = get_pwd_plus_element(p_environ, element);
			if (ft_cd_can_go_to(curpath) == 1)
			{
				ft_list_free(&list);
				return (curpath);
			}
			ft_memdel((void **)&curpath);
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
			curpath = ft_strjoin_(list[i], "/", element);
			curpath = ft_path_trim_free(curpath);
			if (ft_cd_can_go_to(curpath) == 1)
			{
				if (ft_strncmp("/", list[i], 1) == 0)
				{
					ft_dprintf(fds[1], "%s\n", curpath);
				}
				else
				{
					char *to_free;

					to_free = curpath;
					curpath = get_pwd_plus_element(p_environ, to_free);
					ft_memdel((void **)&to_free);
					ft_dprintf(fds[1], "%s\n", curpath);
				}
				ft_list_free(&list);
				return (curpath);
			}
			ft_memdel((void **)&curpath);
			i++;
		}
		ft_list_free(&list);
	}
	return (NULL);
}