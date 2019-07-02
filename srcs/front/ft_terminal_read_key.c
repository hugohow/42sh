/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal_read_key.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 23:11:34 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/21 14:28:35 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Read key of ascii table
*/

int ft_terminal_read_key(void)
{
	int	nread;
	char	seq[4];

	while ((nread = read(STDIN_FILENO, &seq[0], 1)) != 1)
	{
		if (nread == -1)
			return (0);
	}
	if (seq[0] == '\x1b') 
	{
		if (read(STDIN_FILENO, &seq[1], 1) != 1)
		{
			seq[1] = 0;
			return (ft_atoi(seq));
		}
		if (read(STDIN_FILENO, &seq[2], 1) != 1)
		{
			seq[2] = 0;
			return (ft_atoi(seq));
		}
		seq[3] = 0;
		return (ft_atoi(seq));
	}
	else 
	{
		return (seq[0]);
	}
}