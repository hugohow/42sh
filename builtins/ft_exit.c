/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:58:14 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/28 00:23:25 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to exit the shell process
*/

int ft_exit(char **argv, t_env ***p_cpy_environ, int fds[])
{
    int i;
	char *line;

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
				ft_env_add("EXIT", "1", p_cpy_environ, 1);
                return(2);
            }
            i++;
        }
        if (argv[2])
        {
            ft_putstr_fd("shell: exit: too many arguments\n", fds[2]);
			ft_env_add("EXIT", "0", p_cpy_environ, 1);
            return (EXIT_FAIL);
        }
		ft_env_add("EXIT", "1", p_cpy_environ, 1);
        return (ft_atoi(argv[1]));
    }
	line = ft_env_get_value(*p_cpy_environ, "?");
	ft_env_add("EXIT", "1", p_cpy_environ, 1);
	if (line)
		return (ft_atoi(line));
	return (EXIT_SUCCESS);
}