/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bins_table_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 23:03:23 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/03 21:34:03 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ht	*ft_bins_table_get(t_env **copy_environ)
{
	t_vars 	*p_vars;

	(void)copy_environ;
	p_vars = ft_vars_get();
	return (p_vars->hash_table);
}