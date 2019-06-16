/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 19:57:57 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 14:19:06 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#define BUF_SIZE 20
# define FLAG_P (2 << 1)
# define FLAG_L (2 << 2)

int is_file(char *path)
{
    struct stat fileStat;

    if (stat(path, &fileStat) < 0)
        return (-1);
    return (0);
}


int is_symlink(char *path)
{
    struct stat fileStat;

    if (lstat(path, &fileStat) < 0)
        return (0);
    if (S_ISLNK(fileStat.st_mode))
        return (1);
    return (0);
}

char *get_path(size_t size)
{
    char *path;
    char *cwd;

    path = malloc((size) * sizeof(char));

    cwd = getcwd(path, size);
    if (cwd == NULL)
        return (get_path(size * 2));
    return (path);
}

static int ft_change_env(char *new_pwd_line, char *old_pwd_line, t_env ***p_environ)
{
	// printf("new_pwd_line %s \n", new_pwd_line);
	// printf("old_pwd_line %s \n\n", old_pwd_line);
    if (ft_change_line_env("OLDPWD", old_pwd_line, *p_environ) == 0)
        return (-1);
    if (ft_change_line_env("PWD", ft_strjoin("PWD=", new_pwd_line), *p_environ) == 0)
        return (-1);
    return (0);
}

int go_to_root(char *old_pwd_line, t_env ***p_environ)
{
    while (ft_strcmp(get_path(BUF_SIZE), "/") != 0)
        chdir("..");

    if (ft_change_env("/", old_pwd_line, p_environ) < 0)
        return (-1);
    return (0);
}

char *get_absolute_path(char *element)
{
    char *path;

    if (element[0] && element[0] == '/')
        return (element);
    path = ft_strjoin(get_path(BUF_SIZE), "/");
    path = ft_strjoin(path, element);
    return (path);
}

int ft_go_to(char *abs_path)
{
    struct stat fileStat;


	if (stat(abs_path, &fileStat))
	{
		lstat(abs_path, &fileStat);
		if (S_ISLNK(fileStat.st_mode) && access(abs_path, X_OK))
		{
			ft_putstr_fd("Too many symbolic links\n", 2);
			return (-1);
		}
		ft_putstr_fd("No such file or directory\n", 2);
		return (-1);
	}
	else if (!S_ISDIR(fileStat.st_mode) && !S_ISLNK(fileStat.st_mode))
	{
		ft_putstr_fd("not a directory !!!!! \n", 2);
		return (-1);
	}
	else if (access(abs_path, X_OK))
	{
		ft_putstr_fd("permission denied \n", 2);
		return (-1);
	}
    return (chdir(abs_path));
}

int ft_change_dir(char *element, t_env ***p_environ, long long flag)
{
    char *abs_path;
    char *old_pwd_line;

    old_pwd_line = ft_strjoin("OLDPWD=", ft_get_line_env(*p_environ, "PWD") + 4);

	// printf("ancien pwd, get_path %s \n", get_path(BUF_SIZE));
	// printf("ancien pwd, PWD %s \n\n", ft_get_line_env("PWD", p_environ) + 4);
    // définition du chemin absolu
    if (element)
    {
        if (ft_strcmp(element, "/") == 0 || ft_strcmp(element, "/.") == 0)
            return (go_to_root(old_pwd_line, p_environ));
        if (ft_strcmp(element, "-") == 0)
            abs_path = ft_get_line_env(*p_environ, "OLDPWD") + 7;
        else
            abs_path = get_absolute_path(element);
    }
    else
    {
        abs_path = ft_get_line_env(*p_environ, "HOME") + 5;
    }


    if (ft_go_to(abs_path) < 0)
        return (-1);

    // change env et return
    if (is_symlink(abs_path) == 1 && (flag & FLAG_P) == 0)
        return (ft_change_env(abs_path, old_pwd_line, p_environ));
    return (ft_change_env(get_path(BUF_SIZE), old_pwd_line, p_environ));
}

int ft_cd(int argc, char **argv, t_env **cpy_environ, int fds[])
{
    char *element;
	long long flag;

    element = NULL;
	flag = 0;
	if (fds)
	{
		
	}
    if (argc > 1)
	{
		if (ft_strcmp(argv[1], "-P") == 0)
		{
			flag |= FLAG_P;
			argv++;
		}
		else if (ft_strcmp(argv[1], "-L") == 0)
		{
			flag |= FLAG_L;
			argv++;
		}
		element = argv[1];
	}

    return (ft_change_dir(element, &cpy_environ, flag));
}