/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:40:14 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 16:48:56 by hhow-cho         ###   ########.fr       */
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
	if (ft_strchr(cmd, '='))
		return (0);
    while (cmd[i])
    {
        if (cmd[i] == '/')
            return (1);
        i++;
    }
    return (0);
}

static t_ht * ft_get_table_bins(t_env **copy_environ)
{
	int i;

	i = 0;
	while (copy_environ[i])
	{
		if (ft_env_cmp_prefix("PATH", copy_environ[i]->line) == 0)
			return (copy_environ[i]->table);
		i++;
	}
	return (NULL);
}

int ft_exe_bin(t_node *node, t_env ***p_environ, int fds[])
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
	if (ft_strcmp(command, "exit") == 0)
	{
		return (ft_exit(ft_list_size(args), args, *p_environ, fds));
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
    if (ft_strchr(command, '='))
    {
		args[1] = ft_strdup(command);
		args[2] = 0;
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
        return (ft_env(ft_list_size(args), args, *p_environ, fds));
    }
	t_node_ht *value;
	t_ht *table_bins;
	table_bins = ft_get_table_bins(*p_environ);
	value = ft_ht_get(table_bins, command);
	if (value && (char *)(value->datum))
	{
		new_path = (char *)(value->datum);
		result = ft_exe_path(new_path, args, *p_environ, fds);
		return (result);
	}
    else
    {

		DIR *pDir;
		struct dirent *pDirent;
		if ((pDir = opendir (".")))
		{
			while ((pDirent = readdir(pDir)) != NULL) 
			{
				if (ft_strcmp(pDirent->d_name, command) == 0)
				{
					new_path = ft_strjoin(getcwd(NULL, 0), "/");
					new_path = ft_strjoin(new_path, pDirent->d_name);
					result = ft_exe_path(new_path, args, *p_environ, fds);
					closedir (pDir);
					return (result);
				}
			}
		}
		closedir (pDir);
		ft_dprintf(fds[2], "shell: command not found: %s\n", args[0]);
        return (1);
    }
    return (1);
}