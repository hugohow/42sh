/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 00:37:17 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 22:43:04 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	handle_error(char c, int fds[])
{
	ft_dprintf(fds[2], "env: illegal option -- %c\n", c);
	ft_putstr_fd("usage: env [-i] [name=value ...] [utility [argument ...]]\n",\
		fds[2]);
	return (-1);
}

int			ft_env_parse(char ***p_argv, int fds[])
{
	int i;
	int flag;

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
				return (handle_error((**p_argv)[i], fds));
			i++;
		}
		*p_argv = *p_argv + 1;
	}
	return (flag);
}
