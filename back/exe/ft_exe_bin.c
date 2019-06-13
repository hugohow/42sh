/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:40:14 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/09 15:14:42 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "shell.h"

static int ft_list_size(char **list)
{
    int size;

    size = 0;
    while (list[size])
        size++;
    return (size);
}

char *search_path_exe(char *cmd, char *path, char ***p_environ)
{
    DIR *pDir;
    struct dirent *pDirent;

    (void)p_environ;
    if (path == NULL)
        return (NULL);
    if ((pDir = opendir (path)) == NULL)
    {
        return (NULL);
    }
    while ((pDirent = readdir(pDir)) != NULL) 
    {
        if (ft_strcmp(pDirent->d_name, cmd) == 0)
        {
            closedir (pDir);
            return (pDirent->d_name);
        }
    }
    closedir (pDir);
    return (NULL);
}

int is_path(char *cmd)
{
    int i;

    if (cmd == NULL)
        return (-1);
    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '/')
            return (1);
        i++;
    }
    return (0);
}

int ft_exe_bin(char *cmd, t_ht *table_bins, char ***p_environ, int fd0, int fd1, int fd2)
{
    int result;
    char **cmd_list;
    char *command;
    char *new_path;

    cmd_list = ft_strsplit(cmd, ' ');
    if (cmd_list[0] == NULL)
        return 0;
    command = ft_strtrim(cmd_list[0]);
    result = 0;
    new_path = NULL;
    if (is_path(command) == 1)
    {
        cmd_list[0] = "name";
        result = ft_exe_path(command, cmd_list, p_environ, fd0, fd1, fd2);
        return (result);
    }
    if (ft_strcmp(command, "echo") == 0)
    {
        ft_echo(ft_list_size(cmd_list), cmd_list, p_environ, fd0, fd1, fd2);
        return 0;
    }
    if (ft_strcmp(command, "cd") == 0)
    {
        return (ft_cd(ft_list_size(cmd_list), cmd_list, p_environ));
    }
    if (ft_strcmp(command, "setenv") == 0)
    {
        ft_setenv(ft_list_size(cmd_list), cmd_list, p_environ);
        return 0;
    }
    if (ft_strcmp(command, "unsetenv") == 0)
    {
        ft_unsetenv(ft_list_size(cmd_list), cmd_list, p_environ);
        return 0;
    }
    if (ft_strcmp(command, "env") == 0)
    {
        return (ft_env(ft_list_size(cmd_list), cmd_list, p_environ, table_bins));
    }
	t_node_ht *node;
	node = ft_ht_get(table_bins, command);
	if (node && (char *)(node->datum))
	{
		new_path = (char *)(node->datum);
		result = ft_exe_path(new_path, cmd_list, p_environ, fd0, fd1, fd2);
		return (result);
	}
    else
    {
        ft_putstr_fd("shell: command not found: ", fd2);
        ft_putstr_fd(cmd, fd2);
        ft_putstr_fd("\n", fd2);
        return (1);
    }
    return (1);
}