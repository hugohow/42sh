/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_raw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 23:23:34 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 21:10:38 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char **ft_env_raw(t_env **cpy_environ)
{
    char **tab;
    int len;
	int k;

    len = 0;
	k = 0;
    while (cpy_environ[len])
        len++;
    tab = ft_memalloc((len + 1) * sizeof(char *));
    len = 0;
    while (cpy_environ[len])
    {
		if (cpy_environ[len]->special == 0)
        {
			tab[k] = cpy_environ[len]->line;
			k++;
		}
		len++;
    }
    tab[k] = 0;
    return (tab);
}