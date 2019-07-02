/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:56:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/02 00:25:02 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int main(int argc, char **argv)
{
    int success;

    success = 0;
    if (ft_vars_init(argv) != 0)
		return (EXIT_FAIL);
    if (argc > 1 || ft_isatty(0) == 0)
		success = ft_stdin_exec(argv);
    else
		success = ft_terminal_exec();
	ft_vars_free();
    return (success);
}
