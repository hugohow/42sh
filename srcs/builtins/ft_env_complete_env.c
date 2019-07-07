/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_complete_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 00:39:52 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/07 02:11:08 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"




char **ft_env_complete_env(char **argv, t_env ***p_copy_env, int flag, t_env **originial_env)
{
	t_env **copy_env;
	char *prefix;
	char *line;
	int j;
	int i;

	copy_env = *p_copy_env;
	(void)originial_env;
	(void)flag;
	j = 0;
    while (argv[j])
    {
        if (ft_strchr(argv[j], '=') == NULL)
			break ;
		i = 0;
		while ((argv[j])[i] && (argv[j])[i] != '=')
			i++;
		prefix = ft_strsub(argv[j], 0, i);
		line = argv[j] + i + 1;
		ft_env_add(prefix, line, p_copy_env);

if (ft_env_cmp_prefix("PATH", char *line))


		ft_memdel((void **)&prefix);
		j++;
    }
	return (argv + j);
}
