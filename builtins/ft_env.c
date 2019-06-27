/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:58:20 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/27 15:07:27 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

# define FLAG_ENV_I (2 << 0)

/*
** Builtin to get the environnement of the process
*/


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


static char **ft_get_env_variable(char **argv, t_env ***p_copy_env, int flag, t_env **originial_env)
{
	t_env **copy_env;
	char *prefix;
	int path_present;
	int j;

	copy_env = *p_copy_env;
	path_present = 0;
	j = 0;
    while (argv[j])
    {
        if (ft_strchr(argv[j], '=') == NULL)
			break ;
		int i;

		i = 0;
		while ((argv[j])[i] && (argv[j])[i] != '=')
			i++;
		prefix = ft_strsub(argv[j], 0, i);
		if (ft_strcmp("PATH", prefix) == 0)
			path_present = 1;
		ft_env_add(prefix, (argv[j] + i + 1), p_copy_env, 0);
		ft_memdel((void **)&prefix);
		j++;
    }
	if (flag == FLAG_ENV_I && path_present == 0)
	{
		ft_env_add("PATH", ft_env_get_value(originial_env, "PATH"), p_copy_env, 1);
	}
	return (argv + j);
}




static int ft_execute_env(char **argv, int flag, t_env **cpy_environ, int fds[])
{
    int i;
    t_env **copy_env;

    i = 0;
    if (flag == FLAG_ENV_I)
        copy_env = clear_environ();
    else
        copy_env = ft_env_deep_copy(cpy_environ);
	if (copy_env == NULL)
	{
		ft_putstr_fd("Error copy env", 2);
		return (1);
	}
	argv = ft_get_env_variable(argv, &copy_env, flag, cpy_environ);
		int success;
	success = 0;
    if (*argv)
	{
		t_node **root;
		int i;
		char *cmd;

		cmd = ft_memalloc(999 * sizeof(char));
		i = 0;
		while (argv[i])
		{
			cmd = ft_strcat(cmd, argv[i]);
			cmd = ft_strcat(cmd, " ");
			i++;
		}
		if (cmd)
		{
			root = ft_syntax_tree_create(cmd, cpy_environ);
			ft_execute_tree(*root, &copy_env, fds, &success);
			ft_syntax_tree_free(*root);
		}
		else
			ft_print_env(copy_env, fds);	
	}
    else
        ft_print_env(copy_env, fds);
	ft_env_free(&copy_env);
    return (success);
}


static int ft_parse_input_env(char ***p_argv, int fds[])
{
	int k;
	int i;
	int flag;

	k = 0;
	flag = 0;
	while (**p_argv)
	{
		i = 1;
		if ((**p_argv)[0] != '-')
			break ;
		while ((**p_argv)[i])
		{
			if ((**p_argv)[i] == 'i')
				flag = FLAG_ENV_I;
			else
			{
				ft_dprintf(fds[2], "env: illegal option -- %c\n", (**p_argv)[i]);
				ft_putstr_fd("usage: env [-i] [name=value ...] [utility [argument ...]]\n", fds[2]);
				return (1);
			}
				break ;
			i++;
		}
		*p_argv = *p_argv + 1;
	}
	return (flag);
}

int ft_env(char **argv, t_env **cpy_environ, int fds[])
{
    pid_t pid;
    int status;
    int waitstatus;
    int i;
	int flag;

    if (ft_list_size(argv) == 1)
    {
        ft_print_env(cpy_environ, fds);
        return (0);
    }
	flag = 0;
	argv++;
	flag = ft_parse_input_env(&argv, fds);
	if (flag < 0)
		return (1);
    status = 0;
    pid = fork();
    if (pid == 0)
    {
        status = ft_execute_env(argv, flag, cpy_environ, fds);

        exit(status);
    }
    else if (pid < 0)
    {
        ft_putstr_fd("erreur pid", fds[2]);
        exit(1);
    }
	else
	{

	        int w;
        w = waitpid(pid, &waitstatus, WUNTRACED | WCONTINUED);
        if (w == -1) {
            // perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(waitstatus)) {
            // printf("terminé, code=%d\n", WEXITSTATUS(waitstatus));
        } else if (WIFSIGNALED(waitstatus)) {
            printf("tué par le signal %d\n", WTERMSIG(waitstatus));
        } else if (WIFSTOPPED(waitstatus)) {
            printf("arrêté par le signal %d\n", WSTOPSIG(waitstatus));
        } else if (WIFCONTINUED(waitstatus)) {
            printf("relancé\n");
        }
	// }
	}
	// parent
    i = WEXITSTATUS(waitstatus);

    return (i);
}