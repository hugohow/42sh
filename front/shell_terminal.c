/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:07:19 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 22:48:46 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void signal_callback_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n\r", 0);
		ft_putstr_fd(NAME, 0);
		ft_putstr_fd(ft_strrchr(getcwd(NULL, 0), '/') + 1, 0);
		ft_putstr_fd(PROMPT, 0);
	}
}


int shell_terminal(t_env ***p_copy_env)
{
	char *command;
	t_node **root;
	t_config old_config;
	t_config new_config;
	int success;
	int fds[3];

	fds[0] = 0;
	fds[1] = 1;
	fds[2] = 2;
	success = 0;
    if (signal(SIGINT, signal_callback_handler) == SIG_ERR)
        ft_putstr_fd("can't catch SIGINT\n", 2);
	while (42)
	{
		if (ft_terminal_init(&old_config, &new_config) < 0)
		{
			ft_putstr_fd("Init termcaps failed\n", 2);
			exit(EXIT_FAIL);
		}
		ft_putstr_fd("\r", 0);
		ft_putstr_fd(NAME, 0);
		ft_putstr_fd(ft_strrchr(getcwd(NULL, 0), '/') + 1, 0);
		ft_putstr_fd(PROMPT, 0);
		ft_terminal_get_cmd(&command, *p_copy_env);
		root = ft_syntax_tree_create(command, *p_copy_env);
		ft_terminal_exit(&old_config);
		if (root)
			execute_tree(*root, p_copy_env,  fds, &success);
	}
	return (success);
}
