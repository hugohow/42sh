/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 19:57:57 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/25 14:54:24 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to change of directory
*/

static int ft_change_env(char *new_pwd_line, char *old_pwd_line, t_env ***p_environ)
{
	ft_env_add("OLDPWD", old_pwd_line + 7, p_environ, 0);
	ft_env_add("PWD", new_pwd_line, p_environ, 0);
    return (0);
}

// int go_to_root(char *old_pwd_line, t_env ***p_environ)
// {
//     while (ft_strcmp(getcwd(NULL, 0), "/") != 0)
//         chdir("..");

//     if (ft_change_env("/", old_pwd_line, p_environ) < 0)
//         return (1);
//     return (0);
// }

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
	char *pwd;

    if (ft_strncmp("/", element, 1) == 0)
        return (ft_path_trim(element));
    if (ft_strcmp(".", element) == 0 || ft_strcmp("..", element) == 0)
	{
		pwd = ft_env_get_value(*p_environ, "PWD");
		if (pwd == NULL)
			pwd = getcwd(NULL, 0);
		curpath = ft_strjoin(pwd, "/");
		curpath = ft_strjoin(curpath, element);
		curpath = ft_path_trim(curpath);
		return (curpath);
	}
	cd_path = ft_env_get_value(*p_environ, "CDPATH");
	if (cd_path == NULL)
	{
		pwd = ft_env_get_value(*p_environ, "PWD");
		if (pwd == NULL)
			pwd = getcwd(NULL, 0);
		curpath = ft_strjoin(pwd, "/");
		curpath = ft_strjoin(curpath, element);
		curpath = ft_path_trim(curpath);
		return (curpath);
	}
	else
	{
		char **list;

		list = ft_str_separate(cd_path, ':');

		if (ft_strlen(list[0]) == 0)
		{
			curpath = ft_strjoin("./", element);
			if (ft_is_possible_to_go_to(curpath) == 1)
			{
				pwd = ft_env_get_value(*p_environ, "PWD");
				if (pwd == NULL)
					pwd = getcwd(NULL, 0);
				curpath = ft_strjoin(pwd, curpath + 1);
				curpath = ft_path_trim(curpath);
				return (curpath);
			}
			curpath = NULL;
		}

		int i;

		i = 0;
		while (list && list[i])
		{
			if (ft_strlen(list[i]) == 0)
			{
				i++;
				continue ;
			}
			if (ft_strncmp("/", list[i], 1) == 0)
			{
				curpath = ft_strjoin(list[i], "/");
				curpath = ft_strjoin(curpath, element);
				curpath = ft_path_trim(curpath);
				if (ft_is_possible_to_go_to(curpath) == 1)
				{
					ft_putstr_fd(curpath, fds[1]);
					ft_putstr_fd("\n", fds[1]);
					return (curpath);
				}
				curpath = NULL;
			}
			pwd = ft_env_get_value(*p_environ, "PWD");
			if (pwd == NULL)
				pwd = getcwd(NULL, 0);
			curpath = ft_strjoin(pwd, "/");
			curpath = ft_strjoin(curpath, list[i]);
			curpath = ft_strjoin(curpath, "/");
			curpath = ft_strjoin(curpath, element);
			curpath = ft_path_trim(curpath);
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
			return (EXIT_FAIL);
		}
		ft_putstr_fd("No such file or directory : ", fds[2]);
		ft_putstr_fd(curpath, fds[2]);
		ft_putstr_fd("\n", fds[2]);
		return (EXIT_FAIL);
	}
	else if (!S_ISDIR(fileStat.st_mode) && !S_ISLNK(fileStat.st_mode))
	{
		ft_putstr_fd("not a directory !!!!! \n", fds[2]);
		return (EXIT_FAIL);
	}
	else if (access(curpath, X_OK))
	{
		ft_putstr_fd("permission denied \n", fds[2]);
		return (EXIT_FAIL);
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
        // if (ft_strcmp(element, "/") == 0 || ft_strcmp(element, "/.") == 0)
        //     return (go_to_root(old_pwd, p_environ));
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

int ft_cd(char **argv, t_env ***p_cpy_environ, int fds[])
{
	int		flag;
	int argc;

	argv++;
	argc = ft_list_size(argv) - 1;
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
    return (ft_change_dir(argv[0], p_cpy_environ, flag, fds));
}
