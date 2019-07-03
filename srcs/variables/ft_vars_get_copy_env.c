/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars_get_copy_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 00:05:56 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/03 14:47:58 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env     ***ft_vars_get_p_copy_env(void)
{
	t_vars 	*p_vars;

	p_vars = ft_vars_get();
    return (&(p_vars->copy_env));
}

t_env     **ft_vars_get_copy_env(void)
{
	t_vars 	*p_vars;

	p_vars = ft_vars_get();
    return (p_vars->copy_env);
}