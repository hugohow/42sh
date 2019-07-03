/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal_prompt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 23:13:26 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/03 17:14:45 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_terminal_prompt(void)
{
	char *cwd;

	cwd = (char *)ft_vars_get_value(KEY_CWD);
	ft_putchar_fd('\r', 0);
	ft_putstr_fd(NAME, 0);
	ft_putstr_fd(ft_strrchr(cwd, '/'), 0);
	ft_putstr_fd(PROMPT, 0);
}