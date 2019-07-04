/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:58:14 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/04 19:55:23 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to exit the shell process
*/

int ft_exit(char **argv, t_env ***p_cpy_environ, int fds[])
{
    int i;

	(void)p_cpy_environ;
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("shell: exit: too many arguments\n", fds[2]);
		return (EXIT_FAIL);
	}
	*((int *)ft_vars_get_value(KEY_MUST_EXIT)) = 1;
    if (argv[1])
    {
        i = 0;
        while (argv[1][i] && argv[1][i] == ' ')
            i++;
        while (argv[1][i])
        {
            if (ft_isdigit(argv[1][i]) == 0)
            {
                ft_putstr_fd("shell: Numeric argument required\n", fds[2]);
                return (2);
            }
            i++;
        }
        if (argv[2])
        {
            ft_putstr_fd("shell: exit: too many arguments\n", fds[2]);
            return (EXIT_FAIL);
        }
        return (ft_atoi(argv[1]));
    }
	return (*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)));
}