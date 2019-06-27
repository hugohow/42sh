/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:39:27 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/27 13:57:50 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_env_free(t_env ***p_cpy_environ)
{
    size_t i;

    i = 0;
    while ((*p_cpy_environ)[i])
    {
		ft_ht_free(&((*p_cpy_environ)[i]->table));
		ft_memdel((void **)(&((*p_cpy_environ)[i]->line)));
		(*p_cpy_environ)[i]->special = 0;
		ft_memdel((void **)(&((*p_cpy_environ)[i])));
        i++;
    }
	ft_memdel((void **)(p_cpy_environ));
	*p_cpy_environ = NULL;
}