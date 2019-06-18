/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:08:11 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/18 15:55:21 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env **ft_env_copy(t_env **cp_env)
{
    t_env **copy;
    int i;

    i = 0;
    while (cp_env[i])
        i++;
    if (!(copy = (t_env **)ft_memalloc((i + 1) * sizeof(t_env *))))
		return (NULL);
    i = 0;
    while (cp_env[i])
    {
        copy[i] = ft_memalloc(sizeof(t_env));
        copy[i] = cp_env[i];
        i++;
    }
    copy[i] = 0;
    return (copy);
}