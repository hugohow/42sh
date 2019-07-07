/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_get_dest_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 22:05:15 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/07 17:39:58 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char *ft_get_path_home(t_env ***p_environ, int fds[])
{
	char *dest_path;

	if (!(dest_path = ft_strdup(ft_env_get_value(*p_environ, "HOME"))))
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", fds[2]);
		return (NULL);
	}
	return (dest_path);
}

/*
** 1, 2 ) If no directory operand is given and the HOME..
** 3 ) If the directory operand begins with a <slash> character
** 4 ) If the first component of the directory operand is dot or dot-dot
*/

static char *get_dest_path(char *element, t_env ***p_environ, long long flag, int fds[])
{
	char *dest_path;
	char *to_free;

	dest_path = NULL;
    if (!element)
			return (ft_get_path_home(p_environ, fds));
    else if (ft_strncmp("/", element, 1) == 0)
    {
			if (!(dest_path = ft_strdup(element)))
			{
				ft_putstr_fd("minishell: cd: dir error\n", fds[2]);
				return (NULL);
			}
		}
		else
		{
        if (ft_strncmp(element, ".", 1) == 0 || ft_strncmp(element, "..", 2) == 0)
				{
					dest_path = ft_strdup(element);
				}
					else if (ft_strcmp(element, "-") == 0)
				{
					if (!(dest_path = ft_strdup(ft_env_get_value(*p_environ, "OLDPWD"))))
					{
						ft_putstr_fd("minishell: cd: OLDPWD not set\n", fds[2]);
						return (NULL);
					}
					else
						ft_dprintf(fds[1], "%s\n", dest_path);
				}
        else
		{

			char *cd_path;

			cd_path = ft_env_get_value(*p_environ, "CDPATH");
			if (cd_path == NULL)
				dest_path = ft_strjoin("./", element);
			else
				dest_path = ft_cd_get_abs_path_cdpath(p_environ, element, fds, cd_path);
			if (dest_path == NULL)
			{
				ft_dprintf(fds[2], "minishell: No such file or directory: %s\n", element);
				return (NULL);
			}
		}
    }
	if (ft_cd_can_go_to(dest_path) == -1)
	{
		ft_dprintf(fds[2], "minishell: No such file or directory: %s\n", element);
		return (NULL);
	}
	// if flag different de P
	if (~(flag & FLAG_CD_P))
	{
		if (ft_strncmp("/", dest_path, 1) != 0)
		{
			to_free = dest_path;
			dest_path = ft_cd_get_pwd_plus_element(p_environ, to_free);
			ft_memdel((void **)&to_free);
		}
		to_free = dest_path;
		dest_path = ft_path_trim(to_free);
		if (ft_cd_can_go_to(dest_path) == -1)
		{
			ft_putstr_fd("minishell cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory.\n", 2);
			ft_cd_change_env(to_free, p_environ);
			return (NULL);
		}
	}
	dest_path = ft_path_trim(dest_path);
	return (dest_path);
}

char *ft_cd_get_dest_path(char *element, t_env ***p_environ, long long flag, int fds[])
{
	char *dest_path;

	if (!(dest_path = get_dest_path(element, p_environ, flag, fds)))
		return (NULL);
	if (ft_strlen(dest_path) > PATH_MAX)
	{
		ft_memdel((void **)&dest_path);
		ft_putstr_fd("minishell: cd: path too long\n", fds[2]);
		return (NULL);
	}
	return (dest_path);
}