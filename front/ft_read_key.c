/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 23:11:34 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 14:23:58 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Read key of ascii table
*/

int ft_read_key(void)
{
  int	nread;
  char	c;
  char	seq[3];

  while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
  {
    if (nread == -1)
		return (0);
  }
  if (c == '\x1b') 
  {
    if (read(STDIN_FILENO, &seq[0], 1) != 1) return ('\x1b');
    if (read(STDIN_FILENO, &seq[1], 1) != 1) return ('\x1b');
    return ('\x1b');
  }
  else 
  {
    return (c);
  }
}