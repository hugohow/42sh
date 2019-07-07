/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 19:57:57 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/07 22:23:12 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to change of directory
*/

int ft_cd_change_env(char *new_pwd_line, t_env ***p_environ)
{
	char *old_pwd_val;
	char *cwd;
	t_vars 	*p_vars;

	if (ft_env_get_value(*p_environ, "PWD"))
		old_pwd_val = ft_strdup(ft_env_get_value(*p_environ, "PWD"));
	else
	{
		cwd = *((char **)ft_vars_get_value(KEY_CWD));
		old_pwd_val = ft_strjoin("OLDPWD=", cwd);
	}
	p_vars = ft_vars_get();
	ft_memdel((void **)&(p_vars->cwd));
	p_vars->cwd = getcwd(NULL, 0);
	if (new_pwd_line == NULL)
		new_pwd_line = ft_strdup(p_vars->cwd);
	ft_env_add("OLDPWD", old_pwd_val, p_environ);
	ft_env_add("PWD", new_pwd_line, p_environ);
	ft_memdel((void **)&old_pwd_val);
	ft_memdel((void **)&new_pwd_line);
    return (0);
}


int ft_change_dir(char *element, t_env ***p_environ, long long flag, int fds[])
{
    char *dest_path;
	int ret;

	dest_path = ft_cd_get_dest_path(element, p_environ, flag, fds);
	if (dest_path == NULL)
		return (1);	
    if ((ret = ft_cd_go_to(dest_path, fds)) != 0)
	{
		ft_memdel((void **)&dest_path);
		return (ret);
	}
    if (flag & FLAG_CD_P)
	{
		ft_memdel((void **)&dest_path);
		return (ft_cd_change_env(NULL, p_environ));
	}
    return (ft_cd_change_env(dest_path, p_environ));
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
