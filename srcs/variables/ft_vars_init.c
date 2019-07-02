/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 23:57:36 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/02 01:06:34 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_vars_init(char **argv)
{
	t_vars 	*p_vars;
	t_env **copy_env;

	p_vars = ft_vars_get();
    if (!(copy_env = ft_env_copy_raw((char **)environ, argv)))
		return (EXIT_FAIL);
	p_vars->copy_env = copy_env;
    return (0);
}