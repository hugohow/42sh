/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_raw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 23:23:34 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/19 23:21:48 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char **ft_env_raw(t_env **cpy_environ)
{
    char **table_env;
    int len;
	int k;

    len = 0;
	k = 0;
    while (cpy_environ[len])
        len++;
    if (!(table_env = ft_memalloc((len + 1) * sizeof(char *))))
		return (NULL);
    len = 0;
    while (cpy_environ[len])
    {
		if (cpy_environ[len]->special == 0)
        {
			table_env[k] = cpy_environ[len]->line;
			k++;
		}
		len++;
    }
    table_env[k] = 0;
    return (table_env);
}