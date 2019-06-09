/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:53:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/09 10:37:16 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

int ft_get_cmd(int fd, char **command)
{	
    int ret;
	char *command_tmp;
	char *command_tmp1;

    command_tmp = malloc(9999*sizeof(char));
    ret = get_next_line(fd, &command_tmp);
    while (ft_str_brackets_is_valid(command_tmp, ft_strlen(command_tmp)) == 0 && ret >= 0)
    {
        ret = get_next_line(fd, &command_tmp1);
        command_tmp = ft_strjoin(command_tmp, "\n");
        command_tmp = ft_strjoin(command_tmp, command_tmp1);
    }
    *command = command_tmp;
    return (ret);
}