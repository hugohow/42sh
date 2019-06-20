/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:53:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 14:35:08 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


/*
** Read one line of stdin
*/

int ft_get_cmd(char **command)
{	
    int ret;
	char *command_tmp;
	char buff[4];

    command_tmp = ft_memalloc(9999*sizeof(char));
	while (42)
	{
		ret = ft_read_key();
		if (ret == 10)
			break ;
		if (ret != 9)
		{
			ft_putchar_fd((char)ret, STDIN_FILENO);
			buff[0] = (char)ret;
			buff[1] = 0;
			command_tmp = ft_strcat(command_tmp, buff);
		}
	}
	ft_putchar_fd('\n', STDIN_FILENO);
	*command = command_tmp;
    return (ret);
}