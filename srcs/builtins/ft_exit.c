/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 20:11:35 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 20:35:06 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to exit the shell process
*/

static int	handle_error(int fds[])
{
	ft_putstr_fd("shell: Numeric argument required\n", fds[2]);
	return (255);
}

int			ft_exit(char **argv, t_env ***p_cpy_environ, int fds[])
{
	int	i;

	(void)p_cpy_environ;
	*((int *)ft_vars_get_value(KEY_MUST_EXIT)) = 1;
	if (argv[1])
	{
		i = 0;
		while (argv[1][i] && argv[1][i] == ' ')
			i++;
		while (argv[1][i])
		{
			if (ft_isdigit(argv[1][i]) == 0)
				return (handle_error(fds));
			i++;
		}
		if (argv[2])
		{
			ft_putstr_fd("shell: exit: too many arguments\n", fds[2]);
			*((int *)ft_vars_get_value(KEY_MUST_EXIT)) = 0;
			return (EXIT_FAIL);
		}
		return (ft_atoi(argv[1]));
	}
	return (*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)));
}
