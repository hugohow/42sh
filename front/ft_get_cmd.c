/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:53:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/09 02:35:37 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"


static int is_quote_closed(char *cmd)
{
    int i;
    int count_opened;
    int count_closed;

    count_opened = 0;
    count_closed = 0;
    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '"')
        {
            count_opened++;
        }
        i++;
    }
    return (count_opened % 2 != 0);
}

int ft_get_cmd(int fd, char **command)
{	
    int ret;
	char *command_tmp;
	char *command_tmp1;

    command_tmp = malloc(9999*sizeof(char));
    ret = get_next_line(fd, &command_tmp);
    while (is_quote_closed(command_tmp) != 0 && ret >= 0)
    {
        ret = get_next_line(fd, &command_tmp1);
        command_tmp = ft_strjoin(command_tmp, "\n");
        command_tmp = ft_strjoin(command_tmp, command_tmp1);
    }
    *command = command_tmp;
    return (ret);
}