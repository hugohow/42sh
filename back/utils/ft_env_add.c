/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:18:02 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/23 00:15:49 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

static int ft_env_size(t_env **list)
{
    int size;

    size = 0;
    while (list[size])
        size++;
    return (size);
}

void    ft_env_add(char *prefix, char *line, t_env ***p_environ)
{
    t_env **new_environ;
    char *env_line;
    int i;

    new_environ = NULL;
    env_line = ft_strjoin(prefix, "=");
    if (line == NULL)
        env_line = ft_strjoin(env_line, "");
    else
        env_line = ft_strjoin(env_line, line);
    if (ft_env_change_line(prefix, env_line, *p_environ) == 0)
    {
        new_environ = (t_env **)ft_memalloc((ft_env_size(*p_environ) + 2) * sizeof(t_env *));
        i = 0;
        while (i < ft_env_size(*p_environ))
        {
            new_environ[i] = (*p_environ)[i];
            i++;
        }
        new_environ[i] = ft_memalloc(sizeof(t_env));
        new_environ[i]->line = env_line;
        new_environ[i]->special = 0;
        i++;
        new_environ[i] = 0;
        *p_environ = new_environ;
    }
}
