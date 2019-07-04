/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:58:20 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/04 20:39:05 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to get the environnement of the process
*/

void ft_print_env(t_env **cpy_env, int fds[])
{
    int i;

    i = 0;
    while (cpy_env[i])
    {
		ft_putstr_fd(cpy_env[i]->line, fds[1]);
        ft_putstr_fd("\n", fds[1]);
        i++;
    }
}

t_env **clear_environ(void)
{
    t_env **output;

    output = (t_env **)ft_memalloc((sizeof(t_env *) + 1));
    return (output);
}

static char *ft_env_get_cmd(char **argv)
{
	int i;
	int len;
	char *cmd;
	i = 0;
	len = 0;
	while (argv[i])
	{
		len += ft_strlen(argv[i]) + 2;
		i++;
	}
	if (!(cmd = ft_memalloc(len * sizeof(char))))
		return (NULL);
	i = 0;
	while (argv[i])
	{
		cmd = ft_strcat(cmd, argv[i]);
		cmd = ft_strcat(cmd, " ");
		i++;
	}
	return (cmd);
}



static int ft_execute_env(char **argv, int flag, t_env **cpy_environ, int fds[])
{
    int i;
	int success;
    t_env **copy_env;
	char *cmd;

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
	argv = ft_env_complete_env(argv, &copy_env, flag, cpy_environ);
	success = 0;
    if (*argv)
	{
		cmd = ft_env_get_cmd(argv);
		ft_cmd_exec(cmd, &copy_env, fds, &success);
	}
    else
        ft_print_env(copy_env, fds);
	ft_env_free(&copy_env);
    return (success);
}



int ft_env(char **argv, t_env **cpy_environ, int fds[])
{
    pid_t pid;
    int status;
    int waitstatus;
    int i;
	int flag;

	argv++;
    if (ft_list_size(argv) == 0)
    {
        ft_print_env(cpy_environ, fds);
        return (0);
    }
	flag = ft_env_parse(&argv, fds);
	if (flag < 0)
		return (1);
    pid = fork();
	if (pid < 0)
    {
        ft_putstr_fd("erreur pid", fds[2]);
        return (1);
    }
    if (pid == 0)
    {
        status = ft_execute_env(argv, flag, cpy_environ, fds);
        exit(status);
    }
	else
	{
		int w;
		
        w = waitpid(pid, &waitstatus, WUNTRACED | WCONTINUED);
        if (w == -1)
            return (EXIT_FAILURE);
        if (WIFEXITED(waitstatus)) {
            // printf("terminé, code=%d\n", WEXITSTATUS(waitstatus));
        } else if (WIFSIGNALED(waitstatus)) {
            ft_printf("%s\n", ft_errors_signal_get(WTERMSIG(waitstatus)));
        } else if (WIFSTOPPED(waitstatus)) {
            ft_printf("%s\n", ft_errors_stop_get(WTERMSIG(waitstatus)));
        } else if (WIFCONTINUED(waitstatus)) {
            // ft_printf("relancé\n");
        }
	}
    i = WEXITSTATUS(waitstatus);
    return (i);
}