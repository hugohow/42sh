/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_delete_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:00:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 15:00:39 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_env_delete_line(char *key, t_env **cpy_environ)
{
    size_t i;
    size_t j;
    size_t k;
    char *line;

    i = 0;
    while (cpy_environ[i])
    {
        line = (cpy_environ[i])->line;
        if (line[0] == key[0])
        {
            j = 0;
            while (key[j] && line[j] && line[j] == key[j])
            {
                j++;
            }
            if (j == ft_strlen(key))
            {
                k = i + 1;
                while (cpy_environ[k])
                {
                    cpy_environ[k - 1] = cpy_environ[k];
                    k++;
                }
                cpy_environ[k - 1] = cpy_environ[k];
                return (1);
            }
        }
        i++;
    }
    return (0);
}