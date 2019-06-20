/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 19:57:57 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 16:31:13 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to change of directory
*/

int is_symlink(char *path)
{
    struct stat fileStat;

    if (lstat(path, &fileStat) < 0)
        return (0);
    if (S_ISLNK(fileStat.st_mode))
        return (1);
    return (0);
}


static int ft_change_env(char *new_pwd_line, char *old_pwd_line, t_env ***p_environ)
{
    if (ft_env_change_line("OLDPWD", old_pwd_line, *p_environ) == 0)
        return (-1);
    if (ft_env_change_line("PWD", ft_strjoin("PWD=", new_pwd_line), *p_environ) == 0)
        return (-1);
    return (0);
}

int go_to_root(char *old_pwd_line, t_env ***p_environ)
{
    while (ft_strcmp(getcwd(NULL, 0), "/") != 0)
        chdir("..");

    if (ft_change_env("/", old_pwd_line, p_environ) < 0)
        return (-1);
    return (0);
}

char *ft_path_trim(char *path)
{
	int i;
	int j;
	char **list;
	char *new_path;

	list = ft_strsplit(path, '/');
	new_path = ft_memalloc((sizeof(char) * (ft_strlen(path) + 1)));
	i = 0;
	while (list[i])
	{
		if (ft_strcmp(list[i], ".") == 0)
		{
			j = i + 1;
			while (list[j])
			{
				list[j - 1] = list[j];
				j++;
			}
			list[j - 1] = 0;
		}
		else if (ft_strcmp(list[i], "..") == 0)
		{
			if (i > 0)
			{
				j = i + 1;
				while (list[j])
				{
					list[j - 2] = list[j];
					j++;
				}
				list[j - 2] = 0;
				i--;
			}
			else
			{
				j = i + 1;
				while (list[j])
				{
					list[j - 1] = list[j];
					j++;
				}
				list[j - 1] = 0;
			}
		}
		else
			i++;
	}
	i = 0;
	ft_strcat(new_path, "/");
	while (list[i])
	{
		ft_strcat(new_path, list[i]);
		if (list[i + 1] != 0)
			ft_strcat(new_path, "/");
		i++;
	}
	return (new_path);
}

int ft_is_possible_to_go_to(char *abs_path)
{
    struct stat fileStat;


	if (stat(abs_path, &fileStat))
	{
		return (-1);
	}
	else if (!S_ISDIR(fileStat.st_mode) && !S_ISLNK(fileStat.st_mode))
	{
		return (-1);
	}
	else if (access(abs_path, X_OK))
	{
		return (-1);
	}
    return (1);
}


char *get_absolute_path(t_env ***p_environ, char *element, int fds[])
{
    char *curpath;
	char *cd_path;

    if (ft_strncmp("/", element, 1) == 0)
        return (element);
    if (ft_strcmp(".", element) == 0 || ft_strcmp("..", element) == 0)
	{
		curpath = ft_strjoin(ft_env_get_value(*p_environ, "PWD"), "/");
		curpath = ft_strjoin(curpath, element);
		curpath = ft_path_trim(curpath);
		return (curpath);
	}
	cd_path = ft_env_get_value(*p_environ, "CDPATH");
	if (cd_path == NULL)
	{
		curpath = ft_strjoin(ft_env_get_value(*p_environ, "PWD"), "/");
		curpath = ft_strjoin(curpath, element);
		curpath = ft_path_trim(curpath);
		return (curpath);
	}
	else
	{
		char **list;

		cd_path = cd_path + 7;
		list = ft_strsplit(cd_path, ':');

		if (list && list[0])
		{
			// il faut gerer le cas ou y'a un slash

			curpath = ft_strjoin(list[0], "/");
			curpath = ft_strjoin(curpath, element);
			if (ft_is_possible_to_go_to(curpath) == 1)
			{
				ft_putstr_fd(curpath, fds[1]);
				ft_putstr_fd("\n", fds[1]);
				return (curpath);
			}
			curpath = NULL;
		}
		curpath = ft_strjoin("./", element);
		if (ft_is_possible_to_go_to(curpath) == 1)
			return (curpath);
		curpath = NULL;

		int i;

		i = 1;
		while (list[i])
		{
			curpath = ft_strjoin(list[i], "/");
			curpath = ft_strjoin(curpath, element);
			if (ft_is_possible_to_go_to(curpath) == 1)
			{
				ft_putstr_fd(curpath, fds[1]);
				ft_putstr_fd("\n", fds[1]);
				return (curpath);
			}
			curpath = NULL;
			i++;
		}
	}
	return (NULL);
}


int ft_go_to(char *curpath, int fds[])
{
    struct stat fileStat;


	if (stat(curpath, &fileStat))
	{
		lstat(curpath, &fileStat);
		if (S_ISLNK(fileStat.st_mode) && access(curpath, X_OK))
		{
			ft_putstr_fd("Too many symbolic links\n", fds[2]);
			return (-1);
		}
		ft_putstr_fd("No such file or directory\n", fds[2]);
		return (127);
	}
	else if (!S_ISDIR(fileStat.st_mode) && !S_ISLNK(fileStat.st_mode))
	{
		ft_putstr_fd("not a directory !!!!! \n", fds[2]);
		return (-1);
	}
	else if (access(curpath, X_OK))
	{
		ft_putstr_fd("permission denied \n", fds[2]);
		return (-1);
	}
    return (chdir(curpath));
}

int ft_change_dir(char *element, t_env ***p_environ, long long flag, int fds[])
{
    char *curpath;
    char *old_pwd;

	if (ft_env_get_value(*p_environ, "PWD"))
	{
		old_pwd = ft_strjoin("OLDPWD=", ft_env_get_value(*p_environ, "PWD"));
	}
	else
	{
		old_pwd = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	}
    if (element)
    {
        if (ft_strcmp(element, "/") == 0 || ft_strcmp(element, "/.") == 0)
            return (go_to_root(old_pwd, p_environ));
        if (ft_strcmp(element, "-") == 0)
		{
			if (!(curpath = ft_env_get_value(*p_environ, "OLDPWD")))
			{
				ft_putstr_fd("shell: cd: OLDPWD not set\n", fds[2]);
				return (1);
			}
			ft_putstr_fd(curpath, fds[1]);
			ft_putstr_fd("\n", fds[1]);
		}
        else
		{
			curpath = get_absolute_path(p_environ, element, fds);
			if (curpath == NULL)
			{
				ft_putstr_fd("No such file or directory\n", fds[2]);
				return (1);
			}
		}
    }
    else
    {
		if (!(curpath = ft_env_get_value(*p_environ, "HOME")))
		{
			ft_putstr_fd("shell: cd: HOME not set\n", 2);
			return (1);
		}
    }
	if (ft_strlen(curpath) > PATH_MAX)
	{
		ft_putstr_fd("shell: cd: path too long\n", 2);
		return (1);
	}
	int ret;
    if ((ret = ft_go_to(curpath, fds)) != 0)
        return (ret);
    if (flag & FLAG_CD_P)
        return (ft_change_env(getcwd(NULL, 0), old_pwd, p_environ));
    return (ft_change_env(curpath, old_pwd, p_environ));
}

static int parse_input(int *p_argc, char ***p_argv)
{
	int flag;
	int j;

	flag = FLAG_CD_L;
	while (**p_argv && (**p_argv)[0] == '-')
	{
		j = 1;
		if ((**p_argv)[j] == 0)
			return (flag);
		while ((**p_argv)[j])
		{
			if ((**p_argv)[j] == 'L')
				flag = FLAG_CD_L;
			else if ((**p_argv)[j] == 'P')
				flag = FLAG_CD_P;
			else
			{
				ft_dprintf(2, "42sh: cd: -%c: invalid option\n", (**p_argv)[j]);
				return (1);
			}
			j++;
		}
		*p_argv = *p_argv + 1;
		*p_argc = *p_argc - 1;
	}
	return (flag);
}

int ft_cd(int argc, char **argv, t_env **cpy_environ, int fds[])
{
	int		flag;

	argv++;
	argc--;
	flag = parse_input(&argc, &argv);
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
    return (ft_change_dir(argv[0], &cpy_environ, flag, fds));
}
