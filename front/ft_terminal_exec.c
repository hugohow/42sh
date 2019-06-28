/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 23:12:34 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/28 14:22:45 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void signal_callback_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 0);
		ft_terminal_prompt();
	}
	if (signum == SIGTSTP)
	{
		
	}
}


int ft_terminal_exec(t_env ***p_copy_env)
{
	char *command;
	t_node *root;
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
    if (signal(SIGTSTP, signal_callback_handler) == SIG_ERR)
        ft_putstr_fd("can't catch SIGTSTP\n", 2);
	while (42)
	{
		if (ft_terminal_init(&old_config, &new_config, *p_copy_env) < 0)
		{
			ft_putstr_fd("Init termcaps failed\n", 2);
			exit(EXIT_FAIL);
		}
		ft_terminal_prompt();
		ft_terminal_get_cmd(&command, *p_copy_env);
		ft_terminal_exit(&old_config);
		root = ft_syntax_tree_create(command, *p_copy_env);
		ft_execute_tree(root, p_copy_env,  fds, &success);
		ft_syntax_tree_free(&root);
		ft_memdel((void **)&command);
		if (ft_env_get_value(*p_copy_env, "EXIT") && ft_strchr(ft_env_get_value(*p_copy_env, "EXIT"), '1'))
		{
			ft_putstr_fd("exit\n", fds[1]);
			break ;
		}
	}
	return (success);
}
