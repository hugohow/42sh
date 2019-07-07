/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 00:15:54 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/07 20:37:50 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_vars_free(void)
{
	t_vars 	*p_vars;

	p_vars = ft_vars_get();
	ft_env_free(&(p_vars->copy_env));
	ft_memdel((void **)&(p_vars->cwd));
	ft_ht_free(p_vars->p_hash_table);

	ft_memdel((void **)&p_vars);
}