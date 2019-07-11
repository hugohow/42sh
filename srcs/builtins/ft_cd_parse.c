/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:44:27 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/11 17:18:28 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	handle_error(char c)
{
	ft_dprintf(2, "minishell: cd: -%c: invalid option\n", c);
	return (-1);
}

int			ft_cd_parse(int *p_argc, char ***p_argv)
{
	int	flag;
	int	j;

	flag = FLAG_CD_L;
	while (**p_argv && (**p_argv)[0] == '-')
	{
		j = 1;
		if ((**p_argv)[j] == 0)
			return (flag);
		if ((**p_argv)[j] == '-' && (**p_argv)[j + 1] == 0)
		{
			*p_argv = *p_argv + 1;
			*p_argc = *p_argc - 1;
			return (flag);	
		}
		while ((**p_argv)[j])
		{
			if ((**p_argv)[j] == 'L')
				flag = FLAG_CD_L;
			else if ((**p_argv)[j] == 'P')
				flag = FLAG_CD_P;
			else
				return (handle_error((**p_argv)[j]));
			j++;
		}
		*p_argv = *p_argv + 1;
		*p_argc = *p_argc - 1;
	}
	return (flag);
}
