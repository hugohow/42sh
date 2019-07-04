/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_get_dest_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 22:05:15 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/04 19:38:01 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char *get_dest_path(char *element, t_env ***p_environ, int fds[])
{
	char *dest_path;

	dest_path = NULL;
    if (element)
    {
        if (ft_strcmp(element, "-") == 0)
		{
			if (!(dest_path = ft_strdup(ft_env_get_value(*p_environ, "OLDPWD"))))
				ft_putstr_fd("minishell: cd: OLDPWD not set\n", fds[2]);
			else
				ft_dprintf(fds[1], "%s\n", dest_path);
		}
        else
		{
			dest_path = ft_cd_get_abs_path(p_environ, element, fds);
			if (dest_path == NULL)
				ft_dprintf(fds[2], "minishell: No such file or directory: %s\n", element);
		}
    }
    else
    {
		if (!(dest_path = ft_strdup(ft_env_get_value(*p_environ, "HOME"))))
			ft_putstr_fd("minishell: cd: HOME not set\n", fds[2]);
    }
	return (dest_path);
}

char *ft_cd_get_dest_path(char *element, t_env ***p_environ, int fds[])
{
	char *dest_path;

	if (!(dest_path = get_dest_path(element, p_environ, fds)))
		return (NULL);
	if (ft_strlen(dest_path) > PATH_MAX)
	{
		ft_memdel((void **)&dest_path);
		ft_putstr_fd("minishell: cd: path too long\n", fds[2]);
		return (NULL);
	}
	return (dest_path);
}