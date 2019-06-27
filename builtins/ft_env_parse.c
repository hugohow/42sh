/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 00:37:17 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/28 00:37:49 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_env_parse(char ***p_argv, int fds[])
{
	int k;
	int i;
	int flag;

	k = 0;
	flag = 0;
	while (**p_argv)
	{
		i = 1;
		if ((**p_argv)[0] != '-')
			break ;
		while ((**p_argv)[i])
		{
			if ((**p_argv)[i] == 'i')
				flag = FLAG_ENV_I;
			else
			{
				ft_dprintf(fds[2], "env: illegal option -- %c\n", (**p_argv)[i]);
				ft_putstr_fd("usage: env [-i] [name=value ...] [utility [argument ...]]\n", fds[2]);
				return (1);
			}
				break ;
			i++;
		}
		*p_argv = *p_argv + 1;
	}
	return (flag);
}