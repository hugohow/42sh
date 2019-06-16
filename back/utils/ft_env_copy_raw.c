/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_copy_raw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:12:28 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 15:12:31 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

t_env **ft_env_copy_raw(char **str)
{
    t_env **copy;
    int i;

    i = 0;
    while (str[i])
        i++;
    copy = (t_env **)ft_memalloc((i + 1) * sizeof(t_env *));
    i = 0;
    while (str[i])
    {
        copy[i] = ft_memalloc(sizeof(t_env));
        copy[i]->line = ft_strdup(str[i]);
        copy[i]->special = 0;
        i++;
    }
    copy[i] = 0;
    return (copy);
}
