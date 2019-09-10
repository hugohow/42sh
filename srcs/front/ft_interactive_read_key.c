/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interactive_read_key.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <kesaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 23:11:34 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/09/07 18:55:02 by kesaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Read key of ascii table
*/

int	ft_interactive_read_key(void)
{
	int		nread;
	char	seq[4];

	ft_memset(seq, '\0', 4);
	while ((nread = read(STDIN_FILENO, &seq[0], 1)) != 1)
	{
		if (nread == -1)
			return (0);
	}
	if (seq[0] == '\x1b')
	{
		if (read(STDIN_FILENO, &seq[1], 1) != 1)
			return (ft_atoi(seq));
		if (read(STDIN_FILENO, &seq[2], 1) != 1)
			return (ft_atoi(seq));
		return (*(int*)seq);
	}
	else
	{
		return (seq[0]);
	}
}
