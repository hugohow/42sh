/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_delete_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:00:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/06 20:26:56 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_env_delete_line(char *prefix, t_env **cpy_environ)
{
    size_t i;
    size_t k;
	t_vars 	*p_vars;

	p_vars = ft_vars_get();
    i = 0;
	if (ft_strcmp(prefix, "PATH") == 0)
	{
		ft_ht_free(&(p_vars->hash_table));
	}
    while (cpy_environ[i])
    {
		if (ft_env_cmp_prefix(prefix, cpy_environ[i]->line) == 0)
		{
			k = i + 1;
			ft_memdel((void **)&(cpy_environ[i]->line));
			ft_memdel((void **)&(cpy_environ[i]));
			while (cpy_environ[k])
			{
				cpy_environ[k - 1] = cpy_environ[k];
				k++;
			}
			cpy_environ[k - 1] = 0;
			return (1);
		}
        i++;
    }
    return (0);
}