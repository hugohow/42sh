/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 14:58:53 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/18 16:51:19 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *ft_env_get_line(t_env **cpy_environ, char *key)
{
    size_t i;

    i = 0;
    while (cpy_environ[i])
    {
		if (ft_env_cmp_prefix(key, cpy_environ[i]->line) == 0)
		{
			return (cpy_environ[i]->line);
		}
        i++;
    }
    return (NULL);
}

char *ft_env_get_line_n(t_env **cpy_environ, char *str, size_t n)
{
    size_t i;
    size_t j;
    char *line_i;

    i = 0;
    while (cpy_environ[i])
    {
        line_i = (cpy_environ[i])->line;
        if (ft_toupper(line_i[0]) == ft_toupper(str[0]))
        {
            j = 0;
            while (str[j] && line_i[j] && ft_toupper(line_i[j]) == ft_toupper(str[j]))
            {
                j++;
            }
            if (j == n && line_i[j] == '=')
                return (line_i);
        }
        i++;
    }
    return (NULL);
}