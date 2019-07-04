/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interactive_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 23:12:34 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/04 20:48:14 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void signal_callback_handler(int signum)
{
	if (signum == SIGINT)
	{
	}
	if (signum == SIGTSTP)
	{
		
	}
}

static void init_exec_fds(int fds[])
{
	fds[0] = 0;
	fds[1] = 1;
	fds[2] = 2;
    if (signal(SIGINT, signal_callback_handler) == SIG_ERR)
        ft_putstr_fd("can't catch SIGINT\n", 2);
    if (signal(SIGTSTP, signal_callback_handler) == SIG_ERR)
        ft_putstr_fd("can't catch SIGTSTP\n", 2);
}

int ft_interactive_exec(void)
{
	char *command;
	int success;
	int fds[3];
	t_env ***p_copy_env;

	p_copy_env = ft_vars_get_p_copy_env();
	success = 0;
	init_exec_fds(fds);
	while (42)
	{
		if (ft_interactive_init() < 0)
			return (EXIT_FAIL);
		ft_interactive_prompt();
		ft_interactive_get_cmd(&command, *p_copy_env);
		ft_interactive_exit();
		ft_cmd_exec(command, p_copy_env, fds, &success);
		if (*((int *)ft_vars_get_value(KEY_MUST_EXIT)) == 1)
		{
			ft_putstr_fd("exit\n", fds[1]);
			break ;
		}
	}
	return (success);
}
