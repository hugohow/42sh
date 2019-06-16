/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 23:23:34 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 14:27:11 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *ft_get_line_env(t_env **cpy_environ, char *str)
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
            if (j == ft_strlen(str) && line_i[j] == '=')
                return (line_i);
        }
        i++;
    }
    return (NULL);
}

char *ft_get_line_env_n(t_env **cpy_environ, char *str, size_t n)
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

int ft_change_line_env(char *key, char *line, t_env **cpy_environ)
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

int ft_delete_line_env(char *key, t_env **cpy_environ)
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

char **get_env_tab_str(t_env **cpy_environ)
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