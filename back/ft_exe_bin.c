/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:40:14 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 15:31:58 by hhow-cho         ###   ########.fr       */
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

int ft_exe_bin(t_node *node, t_ht *table_bins, t_env ***p_environ, int fds[])
{
    int result;
    char *command;
    char *new_path;
	char **args;

	args = node->args;
	if (args[0] == NULL)
        return 0;
    command = ft_strtrim(args[0]);
    result = 0;
    new_path = NULL;
    if (is_path(command) == 1)
    {
		args[0] = ft_strcpy(args[0], "name");
        result = ft_exe_path(command, args, *p_environ, fds);
        return (result);
    }
    if (ft_strcmp(command, "echo") == 0)
    {
        ft_echo(ft_list_size(args), args, *p_environ, fds);
        return 0;
    }
    if (ft_strcmp(command, "cd") == 0)
    {
        return (ft_cd(ft_list_size(args), args, *p_environ, fds));
    }
    if (ft_strcmp(command, "setenv") == 0)
    {
        ft_setenv(ft_list_size(args), args, p_environ, fds);
        return 0;
    }
    if (ft_strcmp(command, "unsetenv") == 0)
    {
        ft_unsetenv(ft_list_size(args), args, *p_environ, fds);
        return 0;
    }
    if (ft_strcmp(command, "env") == 0)
    {
        return (ft_env(ft_list_size(args), args, *p_environ, fds, table_bins));
    }
	t_node_ht *value;
	value = ft_ht_get(table_bins, command);
	if (value && (char *)(value->datum))
	{
		new_path = (char *)(value->datum);
		result = ft_exe_path(new_path, args, *p_environ, fds);
		return (result);
	}
    else
    {
        ft_putstr_fd("shell: command not found: ", fds[2]);
        ft_putstr_fd(args[0], fds[2]);
        ft_putstr_fd("\n", fds[2]);
        return (1);
    }
    return (1);
}