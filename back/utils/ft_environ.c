#include "shell.h"

t_env **copy_environ_from_str(char **str)
{
    t_env **copy;
    int i;

    i = 0;
    while (str[i])
        i++;
    copy = (t_env **)ft_memalloc((i + 1) * sizeof(t_env *));
    i = 0;
    while (str[i])
    {
        copy[i] = ft_memalloc(sizeof(t_env));
        copy[i]->line = ft_strdup(str[i]);
        copy[i]->special = 0;
        i++;
    }
    copy[i] = 0;
    return (copy);
}


t_env **copy_environ(t_env **cp_env)
{
    t_env **copy;
    int i;

    i = 0;
    while (cp_env[i])
        i++;
    copy = (t_env **)ft_memalloc((i + 1) * sizeof(t_env *));
    i = 0;
    while (cp_env[i])
    {
        copy[i] = ft_memalloc(sizeof(t_env));
        copy[i] = cp_env[i];
        i++;
    }
    copy[i] = 0;
    return (copy);
}


char **get_paths(t_env **copy_env)
{
    char *path_line;
    char **paths;

    path_line = ft_get_line_env(copy_env, "PATH");
    if (path_line)
        path_line = ft_strjoin(ft_get_line_env(copy_env, "PATH"), ":.") + 5;
    else
        path_line = "/usr/sbin:/usr/bin:/sbin:/bin:.";
    paths = ft_strsplit(path_line, ':');
    return (paths);
}