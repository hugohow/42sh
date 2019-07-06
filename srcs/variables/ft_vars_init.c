/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 23:57:36 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/06 21:37:58 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_vars_init(int argc, char **argv)
{
	t_vars 	*p_vars;
	t_env **copy_env;

	p_vars = ft_vars_get();
	p_vars->cwd = getcwd(NULL, 0);
	p_vars->must_exit = 0;
	p_vars->success_exit = 0;
	p_vars->pid = getpid();
	p_vars->argv_list = argv;
	p_vars->argc = argc;
	p_vars->last_key = 0;
    if (!(copy_env = ft_env_copy_raw((char **)environ, argv)))
		return (EXIT_FAIL);
	p_vars->copy_env = copy_env;
    return (0);
}