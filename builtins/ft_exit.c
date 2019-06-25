/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:58:14 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/25 10:09:39 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to exit the shell process
*/

int ft_exit(int argc, char **argv, t_env **cpy_environ, int fds[])
{
    int i;
	char *line;

	(void)argc;
    if (argv[1])
    {
        i = 0;
        while (argv[1][i] && argv[1][i] == ' ')
            i++;
        while (argv[1][i])
        {
            if (ft_isdigit(argv[1][i]) == 0)
            {
                ft_putstr_fd("Numeric argument required", fds[2]);
                exit(EXIT_FAIL);
            }
            i++;
        }
        if (argv[2])
        {
            ft_putstr_fd("Too many arguments Argument list too long", fds[2]);
            return (EXIT_FAIL);
        }
        exit(ft_atoi(argv[1]));
    }
	line = ft_env_get_value(cpy_environ, "?");
	if (line)
		exit(ft_atoi(line));
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}