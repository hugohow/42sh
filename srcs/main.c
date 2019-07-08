/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:56:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 14:30:54 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int main(int argc, char **argv)
{
    int success;

    if (ft_vars_init(argc, argv) != 0)
		return (EXIT_FAIL);
    if (argc > 1 || ft_isatty(0) == 0)
		  ft_non_interactive_exec(argv);
    else
		  ft_interactive_exec();
    success = *((int *)ft_vars_get_value(KEY_SUCCESS_EXIT));
	  ft_vars_free();
    return (success);
}
