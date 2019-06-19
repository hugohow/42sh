/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:53:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/19 23:43:47 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


/*
** Read entirely stdin
*/

int ft_get_cmd(int fd, char **command)
{	
    int ret;
	char *command_tmp;
	char *command_tmp1;

    command_tmp = ft_memalloc(9999*sizeof(char));
	if (fd == 0 && ft_isatty(0))
	{
		char buff[10];

		while (ft_strchr(command_tmp, '\n') == NULL)
		{
			ret = ft_read_key();
			char c;
			c = (char)ret;

				if (ret == 10)
				{
					break;
				}
				if (ret != 9)
				{
					write(0, &c, 1);
					buff[0] = (char)ret;
					buff[1] = 0;
					command_tmp = ft_strcat(command_tmp, buff);
				}
				else
				{

				}
			// if (ret != '\x1b') 
			// {
			// }
			// else
			// {
			// 	if (read(STDIN_FILENO, buff, 1) != 1)
			// 	{

			// 	}
			// 	if (read(STDIN_FILENO, buff, 1) != 1)
			// 	{

			// 	}
			// }
		}
		ft_putchar_fd('\n', 0);
		*command = command_tmp;
	}
	else
	{

		ret = get_next_line(fd, &command_tmp);
		while (ft_str_brackets_is_valid(command_tmp, ft_strlen(command_tmp)) == 0 && ret >= 0)
		{
			ret = get_next_line(fd, &command_tmp1);
			command_tmp = ft_strjoin(command_tmp, "\n");
			command_tmp = ft_strjoin(command_tmp, command_tmp1);
		}
		*command = command_tmp;
	}
    return (ret);
}