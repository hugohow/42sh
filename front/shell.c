/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:56:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 14:50:05 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void signal_callback_handler(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n$> ", 0);
}


int main(int argc, char **argv)
{
    char *command;
    t_env **copy_env;
    int fd;
    int success;
    t_node **root;

    if (signal(SIGINT, signal_callback_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");


    success = 0;
    if (!(copy_env = ft_env_copy_raw((char **)environ, argv)))
	{
		ft_putstr_fd("Failed to copy env\n", 2);
		return (0);
	}
	int fds[3];

	fds[0] = 0;
	fds[1] = 1;
	fds[2] = 2;

    if (argc > 1 || ft_isatty(0) == 0)
    {
        fd = ft_isatty(0) == 0 ? 0 : open(argv[1], O_RDONLY);
        while (get_next_line(fd, &command) != 0)
        {
            root = ft_parse_cmd(command, copy_env);
			if (root)
    			execute_tree(*root, &copy_env,  fds, &success);
	    }
    }
    else
    {

		t_config old_config;
		t_config new_config;


	

		ft_terminal_init(&old_config, &new_config);
        while (42)
        {
			ft_putstr_fd("$> ", 0);
			ft_get_cmd(&command);
            root = ft_parse_cmd(command, copy_env);
			if (root)
    			execute_tree(*root, &copy_env,  fds, &success);
        }
		ft_terminal_exit(&old_config);



    }
	ft_env_free(&copy_env);
    return (success);
}
