/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:30:19 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 17:30:51 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_env_free(t_env ***p_cpy_environ)
{
	size_t	i;

	i = 0;
	while ((*p_cpy_environ)[i])
	{
		if ((*p_cpy_environ)[i]->line)
			ft_memdel((void **)(&((*p_cpy_environ)[i]->line)));
		ft_memdel((void **)(&((*p_cpy_environ)[i])));
		i++;
	}
	ft_memdel((void **)(p_cpy_environ));
	*p_cpy_environ = NULL;
}
