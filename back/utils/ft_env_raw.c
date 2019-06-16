/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_raw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 23:23:34 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 15:10:36 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char **ft_env_raw(t_env **cpy_environ)
{
    char **tab;
    int len;

    len = 0;
    while (cpy_environ[len])
        len++;
    tab = ft_memalloc((len + 1) * sizeof(char *));
    len = 0;
    while (cpy_environ[len])
    {
        tab[len] = cpy_environ[len]->line;
        len++;
    }
    tab[len] = 0;
    return (tab);
}