/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_get_pwd_plus_element.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 22:02:13 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/06 22:44:23 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *ft_cd_get_pwd_plus_element(t_env ***p_environ, char *element)
{
    char *dest_path;
	char *pwd;

	pwd = ft_env_get_value(*p_environ, "PWD");
	if (pwd == NULL)
		pwd = *((char **)ft_vars_get_value(KEY_CWD));
	dest_path = ft_strjoin_(pwd, "/", element);
	// if (ft_cd_can_go_to(dest_path) == 1)
	// 	dest_path = ft_path_trim_free(dest_path);
	return (dest_path);
}