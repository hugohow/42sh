#include "shell.h"

static int ft_list_size(t_env **list)
{
    int size;

    size = 0;
    while (list[size])
        size++;
    return (size);
}

void ft_setenv_args(char *prefix, char *line, t_env ***p_environ)
{
    t_env **new_environ;
    char *env_line;
    int i;

    new_environ = NULL;
    env_line = ft_strjoin(prefix, "=");
    if (line == NULL)
        env_line = ft_strjoin(env_line, "");
    else
        env_line = ft_strjoin(env_line, line);
    if (ft_change_line_env(prefix, env_line, *p_environ) == 0)
    {
        new_environ = (t_env **)malloc((ft_list_size(*p_environ) + 2) * sizeof(t_env *));
        i = 0;
        while (i < ft_list_size(*p_environ))
        {
            new_environ[i] = (*p_environ)[i];
            i++;
        }
        new_environ[i] = ft_memalloc(sizeof(t_env));
        new_environ[i]->line = env_line;
        new_environ[i]->special = 0;
        i++;
        new_environ[i] = 0;
        *p_environ = new_environ;
    }
}

int ft_setenv(int argc, char **argv, t_env ***p_environ, int fds[])
{
    if (argc > 3)
    {
        ft_putstr_fd("setenv: Too many arguments.\n", fds[2]);
        return (0);
    }
    if (argc == 1)
    {
        ft_print_env(*p_environ, fds);
        return (0);
    }
    if (ft_isdigit(argv[1][0]))
    {
        ft_putstr_fd("not valid. must begin with a letter\n", fds[2]);
        return (-1);
    }
    if (argc == 2)
    {
        int i;

        i = 0;
        while (argv[1][i] && argv[1][i] != '=')
            i++;
        ft_setenv_args(ft_strsub(argv[1], 0, i), argv[1] + i + 1, p_environ);
    }
    else
    {
        ft_setenv_args(argv[1], argv[2], p_environ);
    }

    return (0);
}