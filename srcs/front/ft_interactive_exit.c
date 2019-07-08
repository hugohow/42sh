/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interactive_exit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 23:23:04 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 21:22:48 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Terminal exit and configure the former config
*/

void	ft_interactive_exit(void)
{
	t_vars	*p_vars;

	p_vars = ft_vars_get();
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &(p_vars->old_config));
}
