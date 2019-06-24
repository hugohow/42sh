/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal_prompt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 23:13:26 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/24 23:16:30 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_terminal_prompt(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	ft_putchar_fd('\r', 0);
	ft_putstr_fd(NAME, 0);
	ft_putstr_fd(ft_strrchr(pwd, '/') + 1, 0);
	ft_putstr_fd(PROMPT, 0);
	ft_memdel((void **)&pwd);
}