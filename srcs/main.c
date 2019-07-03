/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:56:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/03 20:05:14 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int main(int argc, char **argv)
{
    int success;

    success = 0;
    if (ft_vars_init(argc, argv) != 0)
		return (EXIT_FAIL);
    if (argc > 1 || ft_isatty(0) == 0)
		success = ft_non_interactive_exec(argv);
    else
		success = ft_interactive_exec();
	ft_vars_free();
    return (success);
}
