/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_change_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:01:20 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 15:01:32 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_env_change_line(char *key, char *line, t_env **cpy_environ)
{
    size_t i;
    size_t j;
    char *line_i;

    i = 0;
    while (cpy_environ[i])
    {
        line_i = (cpy_environ[i])->line;
        if (line_i[0] == key[0])
        {
            j = 0;
            while (key[j] && line_i[j] && line_i[j] == key[j])
            {
                j++;
            }
            if (j == ft_strlen(key))
            {
                (cpy_environ[i])->line = line;
                return (1);
            }
        }
        i++;
    }
    return (0);
}