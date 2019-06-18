/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:56:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/18 14:35:07 by hhow-cho         ###   ########.fr       */
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
	t_ht *table_bins;
    t_node **root;
    // if ((ft_init_terminal(&orig_termios, &new_termios)) < 0)
    //     return (-1);
    if (signal(SIGINT, signal_callback_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");


    success = 0;
    if (!(copy_env = ft_env_copy_raw((char **)environ, argv)))
	{
		ft_putstr_fd("Failed to copy env\n", 2);
		return (0);
	}
	table_bins = ft_bins_table_create(copy_env);
	int fds[3];

	fds[0] = 0;
	fds[1] = 1;
	fds[2] = 2;

    if (argc > 1 || ft_isatty(0) == 0)
    {
        fd = ft_isatty(0) == 0 ? 0 : open(argv[1], O_RDONLY);
        while (ft_get_cmd(fd, &command) != 0)
        {
            root = ft_parse_cmd(command, copy_env);
			if (root)
    			execute_tree(*root, table_bins, &copy_env,  fds, &success);
	    }
    }
    else
    {
        while (42)
        {
			ft_putstr_fd("\r$> ", 0);
			ft_get_cmd(0, &command);
            root = ft_parse_cmd(command, copy_env);
			if (root)
    			execute_tree(*root, table_bins, &copy_env,  fds, &success);
        }
    }
    return (success);
}
