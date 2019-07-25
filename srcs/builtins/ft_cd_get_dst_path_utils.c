/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_get_dst_path_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:55:22 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/25 14:22:54 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_cd_get_path_home(t_env ***p_environ, int fds[])
{
	char *dest_path;

	if (!(dest_path = ft_strdup(ft_env_get_value(*p_environ, "HOME"))))
	{
		ft_putstr_fd("21sh: cd: HOME not set\n", fds[2]);
		return (NULL);
	}
	dest_path = ft_path_trim_free(dest_path);
	return (dest_path);
}

char	*ft_cd_get_absolute_path(char *element, int fds[])
{
	char *dest_path;

	if (!(dest_path = ft_strdup(element)))
	{
		ft_putstr_fd("21sh: cd: dir error\n", fds[2]);
		return (NULL);
	}
	dest_path = ft_path_trim_free(dest_path);
	return (dest_path);
}

char	*ft_cd_get_old_path(t_env ***p_environ, int fds[])
{
	char *dest_path;

	if (!(dest_path = ft_strdup(ft_env_get_value(*p_environ, "OLDPWD"))))
	{
		ft_putstr_fd("21sh: cd: OLDPWD not set\n", fds[2]);
		return (NULL);
	}
	if (ft_cd_can_go_to(dest_path) == 1)
		ft_dprintf(fds[1], "%s\n", dest_path);
	dest_path = ft_path_trim_free(dest_path);
	return (dest_path);
}

char	*ft_cd_get_path_cdpath(char *element, t_env ***p_environ, int fds[])
{
	char *cd_path;
	char *dest_path;

	cd_path = ft_env_get_value(*p_environ, "CDPATH");
	if (cd_path == NULL)
		dest_path = ft_strjoin("./", element);
	else
		dest_path = ft_cd_get_abs_path_cdpath(p_environ, element, fds, cd_path);
	return (dest_path);
}
