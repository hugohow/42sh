/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 19:57:57 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/28 17:09:27 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to change of directory
*/

static int ft_cd_change_env(char *new_pwd_line, char *old_pwd_val, t_env ***p_environ)
{
	if (new_pwd_line == NULL)
		new_pwd_line = getcwd(NULL, 0);
	ft_env_add("OLDPWD", old_pwd_val, p_environ, 0);
	ft_env_add("PWD", new_pwd_line, p_environ, 0);
	ft_memdel((void **)&old_pwd_val);
	ft_memdel((void **)&new_pwd_line);
    return (0);
}

static char *ft_get_curpath(char *element, t_env ***p_environ, int fds[])
{
	char *curpath;

	curpath = NULL;
    if (element)
    {
        if (ft_strcmp(element, "-") == 0)
		{
			if (!(curpath = ft_strdup(ft_env_get_value(*p_environ, "OLDPWD"))))
			{
				ft_putstr_fd("minishell: cd: OLDPWD not set\n", fds[2]);
				return (NULL);
			}
			ft_dprintf(fds[1], "%s\ncurpath", curpath);
		}
        else
		{
			curpath = ft_cd_get_abs_path(p_environ, element, fds);
			if (curpath == NULL)
			{
				ft_dprintf(fds[2], "minishell: No such file or directory: %s\n", element);
				return (NULL);
			}
		}
    }
    else
    {
		if (!(curpath = ft_strdup(ft_env_get_value(*p_environ, "HOME"))))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
    }
	if (ft_strlen(curpath) > PATH_MAX)
	{
		ft_memdel((void **)&curpath);
		ft_putstr_fd("minishell: cd: path too long\n", 2);
		return (NULL);
	}
	return (curpath);
}

int ft_change_dir(char *element, t_env ***p_environ, long long flag, int fds[])
{
    char *curpath;
    char *old_pwd_val;
	int ret;

	if (ft_env_get_value(*p_environ, "PWD"))
		old_pwd_val = ft_strdup(ft_env_get_value(*p_environ, "PWD"));
	else
		old_pwd_val = ft_strjoin_free_second("OLDPWD=", getcwd(NULL, 0));
	curpath = ft_get_curpath(element, p_environ, fds);
	if (curpath == NULL)
	{
		ft_memdel((void **)&old_pwd_val);
		return (1);	
	}
    if ((ret = ft_cd_go_to(curpath, fds)) != 0)
	{
		ft_memdel((void **)&old_pwd_val);
		return (ret);
	}
    if (flag & FLAG_CD_P)
        return (ft_cd_change_env(NULL, old_pwd_val, p_environ));
    return (ft_cd_change_env(curpath, old_pwd_val, p_environ));
}


int ft_cd(char **argv, t_env ***p_cpy_environ, int fds[])
{
	int		flag;
	int argc;
	char *element;
	int ret;

	argv++;
	argc = (int)ft_list_size(argv) - 1;
	flag = ft_cd_parse(&argc, &argv);
	if (flag == -1)
	{
		ft_putstr_fd("cd: usage: cd [-L|[-P] [dir]\n", 2);
		return (1);
	}
    if (argc > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	element = ft_strdup(argv[0]);
	ret = ft_change_dir(element, p_cpy_environ, flag, fds);
	ft_memdel((void **)&element);
    return (ret);
}
