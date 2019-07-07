/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bins_table_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 23:03:23 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/07 20:34:04 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ht	**ft_p_bins_table_get(void)
{
	t_vars 	*p_vars;

	p_vars = ft_vars_get();
	return (p_vars->p_hash_table);
}