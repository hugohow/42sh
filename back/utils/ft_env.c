/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 23:23:34 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/15 23:27:23 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *ft_get_line_env(char **cpy_environ, char *str)
{
    size_t i;
    size_t j;

    i = 0;
    while (cpy_environ[i])
    {

        if (ft_toupper(cpy_environ[i][0]) == ft_toupper(str[0]))
        {
            j = 0;
            while (str[j] && cpy_environ[i][j] && ft_toupper(cpy_environ[i][j]) == ft_toupper(str[j]))
            {
                j++;
            }
            if (j == ft_strlen(str) && cpy_environ[i][j] == '=')
                return (cpy_environ[i]);
        }
        i++;
    }
    return (NULL);
}

char *ft_get_line_env_n(char **cpy_environ, char *str, size_t n)
{
    size_t i;
    size_t j;

    i = 0;
    while (cpy_environ[i])
    {
        if (ft_toupper(cpy_environ[i][0]) == ft_toupper(str[0]))
        {
            j = 0;
            while (str[j] && cpy_environ[i][j] && ft_toupper(cpy_environ[i][j]) == ft_toupper(str[j]))
            {
                j++;
            }
            if (j == n && cpy_environ[i][j] == '=')
                return (cpy_environ[i]);
        }
        i++;
    }
    return (NULL);
}

int ft_change_line_env(char *key, char *line, char **cpy_environ)
{
    size_t i;
    size_t j;

    i = 0;
    while (cpy_environ[i])
    {
        if (cpy_environ[i][0] == key[0])
        {
            j = 0;
            while (key[j] && cpy_environ[i][j] && cpy_environ[i][j] == key[j])
            {
                j++;
            }
            if (j == ft_strlen(key))
            {
                cpy_environ[i] = line;
                return (1);
            }
        }
        i++;
    }
    return (0);
}

int ft_delete_line_env(char *key, char **cpy_environ)
{
    size_t i;
    size_t j;
    size_t k;

    i = 0;
    while (cpy_environ[i])
    {

        if (cpy_environ[i][0] == key[0])
        {
            j = 0;
            while (key[j] && cpy_environ[i][j] && cpy_environ[i][j] == key[j])
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