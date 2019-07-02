/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_complete_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 00:39:52 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/28 00:45:48 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char **ft_env_complete_env(char **argv, t_env ***p_copy_env, int flag, t_env **originial_env)
{
	t_env **copy_env;
	char *prefix;
	int path_present;
	int j;
	int i;

	copy_env = *p_copy_env;
	path_present = 0;
	j = 0;
    while (argv[j])
    {
        if (ft_strchr(argv[j], '=') == NULL)
			break ;
		i = 0;
		while ((argv[j])[i] && (argv[j])[i] != '=')
			i++;
		prefix = ft_strsub(argv[j], 0, i);
		if (ft_strcmp("PATH", prefix) == 0)
			path_present = 1;
		ft_env_add(prefix, (argv[j] + i + 1), p_copy_env, 0);
		ft_memdel((void **)&prefix);
		j++;
    }
	if (flag == FLAG_ENV_I && path_present == 0)
	{
		ft_env_add("PATH", ft_env_get_value(originial_env, "PATH"), p_copy_env, 1);
	}
	return (argv + j);
}