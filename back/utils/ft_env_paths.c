/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:14:14 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 15:14:15 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "shell.h"


char **ft_env_paths(t_env **copy_env)
{
    char *path_line;
    char **paths;

    path_line = ft_env_get_line(copy_env, "PATH");
    if (path_line)
        path_line = ft_strjoin(ft_env_get_line(copy_env, "PATH"), ":.") + 5;
    else
        path_line = "/usr/sbin:/usr/bin:/sbin:/bin:.";
    paths = ft_strsplit(path_line, ':');
    return (paths);
}