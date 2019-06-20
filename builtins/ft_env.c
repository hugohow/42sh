/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:58:20 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 14:46:11 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


typedef struct s_token_env
{
    char *type;
    char flag_type;
    char *string;
}               t_token_env;

void ft_print_env(t_env **cpy_env, int fds[])
{
    int i;

    i = 0;
    while (cpy_env[i])
    {
        if (cpy_env[i]->special == 0)
        {
			ft_putstr_fd(cpy_env[i]->line, fds[1]);
            ft_putstr_fd("\n", fds[1]);
        }
        i++;
    }
}

t_env **clear_environ(void)
{
    t_env **output;

    output = (t_env **)ft_memalloc(sizeof(t_env *));
    return (output);
}

t_token_env *create_token_env(char *type, char flag_type, char *string)
{
    t_token_env *token_env;

    if (!(token_env = ft_memalloc(sizeof(t_token_env))))
		return (NULL);
    token_env->type = type;
    token_env->flag_type = flag_type;
    token_env->string = string;   
    return (token_env);
}

int is_option(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

t_token_env **tokenize_argv(int argc, char **argv)
{
    int i;
    int j;
    int k;
    t_token_env **list;
    char *utility;

    if (!(list = (t_token_env **)ft_memalloc((argc + 3) * sizeof(t_token_env *))))
		return (NULL);
    i = 0;
    k = 0;
    utility = "";
    while (i < argc)
    {
        if (i == 0)
        {
            list[k++] = create_token_env("command", 0, argv[0]);
        }
        else if (argv[i][0] && argv[i][0] == '-')
        {
            j = 1;
            while (argv[i][j])
            {
                if (argv[i][j] == 'i')
                    list[k++] = create_token_env("flag", 'i', NULL);
                else if (argv[i][j] == 'v')
                    list[k++] = create_token_env("flag", 'v', NULL);
                else if (argv[i][j] == 'P')
                {
                    if (argv[i + 1] && argv[i + 1][0] != '-')
                    {
                        list[k++] = create_token_env("flag", 'P', argv[i + 1]);
                        i++;
                    }
                    else
                    {
                        ft_putstr_fd("Error P n'a pas de path\n", 2);
                        exit(-1);
                    }
                }
                else if (argv[i][j] == 'S')
                {
                    if (argv[i + 1] && argv[i + 1][0] != '-')
                    {
                        list[k++] = create_token_env("flag", 'S', argv[i + 1]);
                        i++;
                    }
                    else
                    {
                        ft_putstr_fd("Error S n'a pas de path\n", 2);
                        exit(-1);
                    }
                }
                else if (argv[i][j] == 'u')
                {
                    if (argv[i + 1] && argv[i + 1][0] != '-')
                    {
                        list[k++] = create_token_env("flag", 'u', argv[i + 1]);
                        i++;
                    }
                    else
                    {
                        ft_putstr_fd("Error u n'a pas de path\n", 2);
                        exit(-1);
                    }
                }
                else
                {
                    ft_putstr_fd("Illegal option !", 2);
                    ft_putchar_fd(argv[i][j], 2);
                    ft_putstr_fd("\n", 2);
                    exit(-1);
                }
                j++;
            }
        }
        else
        {
            while (argv[i] && is_option(argv[i]) == 1)
            {
                list[k++] = create_token_env("option", 0, argv[i]);
                i++;
            }
            if (argv[i])
            {
                while (argv[i])
                {
                    utility = ft_strjoin(utility, " ");
                    utility = ft_strjoin(utility, argv[i]);
                    i++;
                }
                list[k++] = create_token_env("utility", 0, utility);
            }
        }

        i++;
    }
    list[k] = 0;
    return (list);
}

int has_i(t_token_env **token_ls)
{
    int i;

    i = 0;
    while (token_ls[i])
    {
        if (token_ls[i]->flag_type == 'i')
            return (1);
        i++;
    }
    return (0);
}

static int execute_ls(t_token_env **token_ls, t_env **cpy_environ, int fds[])
{
    int i;
    int j;
    t_env **copy_env;
    char *tmp;

    i = 0;
    if (has_i(token_ls))
        copy_env = clear_environ();
    else
        copy_env = ft_env_deep_copy(cpy_environ);
	if (copy_env == NULL)
	{
		ft_putstr_fd("Error copy env", 2);
		return (-1);
	}
    while (token_ls[i])
    {
        if (ft_strcmp(token_ls[i]->type, "option") == 0)
        {
            tmp = token_ls[i]->string;
            j = 0;
            while (tmp[j] && tmp[j] != '=')
            {
                j++;
            }
            ft_env_add(ft_strsub(tmp, 0, j), tmp + j + 1, &copy_env);
        }
        i++;
    }
    if (i > 0 && ft_strcmp(token_ls[i - 1]->type, "utility") == 0)
	{
		t_node **root;
		int success;
		int fds[3];

		fds[0] = 0;
		fds[1] = 1;
		fds[2] = 2;
		root = ft_parse_cmd(token_ls[i - 1]->string, cpy_environ);
		success = 0;
    	execute_tree(*root, &copy_env, fds, &success);
		return (success);
	}
    else
        ft_print_env(copy_env, fds);
    return (0);
}

void print_token_ls(t_token_env **token_ls)
{
    int i;

    i = 0;
    while (token_ls[i] != 0)
    {
        // ft_printf("type : %ld \t flag: %c \t string : %s\n", token_ls[i]->type, token_ls[i]->flag_type, token_ls[i]->string);
        i++;
    }
}

int ft_env(int argc, char **argv, t_env **cpy_environ, int fds[])
{
    pid_t pid;
    int status;
    t_token_env **token_ls;
    int waitstatus;
    int i;

	if (fds)
	{
		
	}
    if (argc == 1)
    {
        ft_print_env(cpy_environ, fds);
        return (0);
    }
    status = 0;
    pid = fork();
    if (pid == 0)
    {
        token_ls = tokenize_argv(argc, argv);
        // permet de vérfier si il y a des anomalies
        print_token_ls(token_ls);
        status = execute_ls(token_ls, cpy_environ, fds);
        exit(status);
    }
    else if (pid < 0)
    {
        ft_putstr_fd("erreur pid", fds[2]);
        exit(-1);
    }
    else
    {
        wait(&waitstatus);
        i = WEXITSTATUS(waitstatus);
    }
    return (i);
}