/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interactive_prompt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 23:13:26 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/07 16:43:41 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_interactive_prompt(void)
{
	char *cwd;
	char *folder_name;

	cwd = *((char **)ft_vars_get_value(KEY_CWD));
	ft_putchar_fd('\r', 0);
	ft_putstr_fd(NAME, 0);
	folder_name = ft_strrchr(cwd, '/');
	if (folder_name)
		ft_putstr_fd(folder_name, 0);
	ft_putstr_fd(PROMPT, 0);
}