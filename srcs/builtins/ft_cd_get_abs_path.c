/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_get_abs_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 22:25:10 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/03 22:03:11 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *ft_cd_get_abs_path(t_env ***p_environ, char *element, int fds[])
{
	char *cd_path;

    if (ft_strncmp("/", element, 1) == 0)
        return (ft_path_trim(element));
    if (ft_strcmp(".", element) == 0 || ft_strcmp("..", element) == 0)
		return (ft_cd_get_pwd_plus_element(p_environ, element));
	cd_path = ft_env_get_value(*p_environ, "CDPATH");
	if (cd_path == NULL)
		return (ft_cd_get_pwd_plus_element(p_environ, element));
	return (ft_cd_get_abs_path_cdpath(p_environ, element, fds, cd_path));
}