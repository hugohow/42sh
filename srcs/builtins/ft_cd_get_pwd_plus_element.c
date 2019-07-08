/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_get_pwd_plus_element.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 22:02:13 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 19:06:43 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_cd_get_pwd_plus_element(t_env ***p_env, char *element)
{
	char	*dest_path;
	char	*pwd;

	pwd = ft_env_get_value(*p_env, "PWD");
	if (pwd == NULL)
		pwd = *((char **)ft_vars_get_value(KEY_CWD));
	dest_path = ft_strjoin_(pwd, "/", element);
	return (dest_path);
}
