/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_delete_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:00:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/02 02:55:28 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_env_delete_line(char *prefix, t_env **cpy_environ)
{
    size_t i;

    i = 0;
    while (cpy_environ[i])
    {
		if (ft_env_cmp_prefix(prefix, cpy_environ[i]->line) == 0)
		{
			cpy_environ[i]->special = 1;
			return (1);
		}
        i++;
    }
    return (0);
}