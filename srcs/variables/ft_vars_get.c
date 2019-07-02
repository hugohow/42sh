/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 23:40:30 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/02 00:46:30 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_vars     *ft_vars_get(void)
{
	static t_vars 	*p_vars;

	if (p_vars == NULL)
		p_vars = ft_memalloc(sizeof(t_vars));
    return (p_vars);
}