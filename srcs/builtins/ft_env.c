/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:58:20 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/10 22:22:58 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to get the environnement of the process
*/

void		ft_print_env(t_env **cpy_env, int fds[])
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

t_env		**clear_environ(void)
{
	t_env **output;

	if (!(output = (t_env **)ft_memalloc((sizeof(t_env *) + 1))))
		return (NULL);
	return (output);
}

static char	*ft_env_get_cmd(char **argv)
{
	int		i;
	int		len;
	char	*cmd;

	i = 0;
	len = 0;
	while (argv[i])
	{
		len += ft_strlen(argv[i]) + 2;
		i++;
	}
	if (!(cmd = (char *)ft_memalloc(len * sizeof(char))))
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

// static int ft_execute_env(char **argv, int flag, t_env **cpy_environ, int fds[])
// {
// 	int success;
//     t_env **copy_env;
// 	char *cmd;
// 	t_ht **p_hash;

//     if (flag == FLAG_ENV_I)
//         copy_env = clear_environ();
//     else
//         copy_env = ft_env_deep_copy(cpy_environ);
// 	p_hash = ft_memalloc(sizeof(t_ht *));
// 	if (copy_env == NULL)
// 	{
// 		ft_putstr_fd("Error copy env", 2);
// 		return (1);
// 	}
// 	argv = ft_env_complete_env(argv, &copy_env, p_hash);
// 	success = 0;
//     if (*argv)
// 	{
// 		// if ((ft_find_bin(*argv, p_hash)) < 0)
// 		// {
// 		// 	ft_dprintf(fds[2],
// 		// 		"minishell: command not found: %s\n", *argv);
// 		// 	return (EXIT_UTILITY_NOT_FOUND);
// 		// }
// 		cmd = ft_env_get_cmd(argv);


		
// 		if (*p_hash)
// 		{
// 			ft_cmd_exec(cmd, &copy_env, p_hash, fds);
// 			ft_ht_free(p_hash);
// 		}
// 		else
// 			ft_cmd_exec(cmd, &copy_env, NULL, fds);
// 	}
//     else
//         ft_print_env(copy_env, fds);
// 	ft_env_free(&copy_env);
// 	ft_memdel((void **)&(p_hash));
//     return (*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)));
// }



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

	t_env **copy_env;
	char *cmd;
	t_ht **p_hash;

	if (flag == FLAG_ENV_I)
		copy_env = clear_environ();
	else
		copy_env = ft_env_deep_copy(cpy_environ);
	p_hash = (t_ht **)ft_memalloc(sizeof(t_ht *));
	if (copy_env == NULL)
	{
		ft_putstr_fd("Error copy env", 2);
		return (1);
	}
	argv = ft_env_complete_env(argv, &copy_env, p_hash);
	i = 0;
	if (*argv)
	{
		if ((ft_find_bin(*argv, p_hash)) < 0)
		{
			ft_dprintf(fds[2], \
				"minishell env : command not found: %s\n", *argv);
			i = EXIT_UTILITY_NOT_FOUND;
		}
		else
		{
				pid = fork();
				if (pid < 0)
				{
					ft_putstr_fd("erreur pid", fds[2]);
					return (1);
				}
				if (pid == 0)
				{

						cmd = ft_env_get_cmd(argv);


						
						if (*p_hash)
						{
							ft_cmd_exec(cmd, &copy_env, p_hash, fds);
							ft_ht_free(p_hash);
						}
						else
							ft_cmd_exec(cmd, &copy_env, NULL, fds);
						ft_env_free(&copy_env);
						ft_memdel((void **)&(p_hash));
						status = *((int *)ft_vars_get_value(KEY_SUCCESS_EXIT));
						ft_vars_free();
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
		}



		}
	else
		ft_print_env(copy_env, fds);
	ft_env_free(&copy_env);
	if (*p_hash)
		ft_ht_free(p_hash);
	ft_memdel((void **)&(p_hash));


    return (i);
}