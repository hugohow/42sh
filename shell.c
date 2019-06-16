/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:56:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/16 20:43:54 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
    // if (signal(SIGPIPE, signal_callback_handler) == SIG_ERR)
    //     printf("\ncan't catch SIGWINCH\n");


    success = 0;
    copy_env = ft_env_copy_raw((char **)environ, argv);
	table_bins = ft_bins_table_create(copy_env);
	int fds[3];

	fds[0] = 0;
	fds[1] = 1;
	fds[2] = 2;

    if (argc > 1 || isatty(0) == 0)
    {
        fd = isatty(0) == 0 ? 0 : open(argv[1], O_RDONLY);
        while (ft_get_cmd(fd, &command) != 0)
        {
            root = ft_parse_cmd(command, copy_env);
    		execute_tree(*root, table_bins, &copy_env,  fds, &success);
	    }
    }
    else
    {
        while (42)
        {
			ft_putstr_fd("$> ", 0);
            ft_get_cmd(0, &command);
            root = ft_parse_cmd(command, copy_env);
    		execute_tree(*root, table_bins, &copy_env,  fds, &success);
        }
    }
    return (success);
}
