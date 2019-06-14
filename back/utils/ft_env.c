#include "shell.h"

char *ft_get_line_env(char *str, char **cpy_environ)
{
    size_t i;
    size_t j;

    i = 0;
    while (cpy_environ[i])
    {

        if (cpy_environ[i][0] == str[0])
        {
            j = 0;
            while (str[j] && cpy_environ[i][j] && cpy_environ[i][j] == str[j])
            {
                j++;
            }
            if (j == ft_strlen(str))
                return (cpy_environ[i]);
        }
        i++;
    }
    return (NULL);
}

int ft_change_line_env(char *key, char *line, char **cpy_environ)
{
    size_t i;
    size_t j;

    i = 0;
    while (cpy_environ[i])
    {
        if (cpy_environ[i][0] == key[0])
        {
            j = 0;
            while (key[j] && cpy_environ[i][j] && cpy_environ[i][j] == key[j])
            {
                j++;
            }
            if (j == ft_strlen(key))
            {
                cpy_environ[i] = line;
                return (1);
            }
        }
        i++;
    }
    return (0);
}

int ft_delete_line_env(char *key, char **cpy_environ)
{
    size_t i;
    size_t j;
    size_t k;

    i = 0;
    while (cpy_environ[i])
    {

        if (cpy_environ[i][0] == key[0])
        {
            j = 0;
            while (key[j] && cpy_environ[i][j] && cpy_environ[i][j] == key[j])
            {
                j++;
            }
            if (j == ft_strlen(key))
            {
                k = i + 1;
                while (cpy_environ[k])
                {
                    cpy_environ[k - 1] = cpy_environ[k];
                    k++;
                }
                cpy_environ[k - 1] = cpy_environ[k];
                return (1);
            }
        }
        i++;
    }
    return (0);
}