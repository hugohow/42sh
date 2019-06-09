/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:56:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/09 15:02:42 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_ht *ft_create_table_bins(char **copy_env)
{
	char **paths;
    char *new_path;
    char *d_name;
	int i;
	t_ht *table_bins;

	table_bins = ft_ht_create();
	paths = get_paths(copy_env);
	i = 0;
    while (paths[i])
    {

		DIR *pDir;
		struct dirent *pDirent;

		if ((pDir = opendir (paths[i])) == NULL)
		{
			break;
		}
		while ((pDirent = readdir(pDir)) != NULL) 
		{
            new_path = ft_strjoin(paths[i], "/");
            new_path = ft_strjoin(new_path, d_name);
			ft_ht_add(table_bins, d_name, (void *)(new_path));
		}
		closedir (pDir);
        i++;
    }

	return (table_bins);
}

int main(int argc, char **argv)
{
    char *command;
    char **copy_env;
    int fd;
    int success;
	t_ht *table_bins;
    t_node **root;
    // if ((ft_init_terminal(&orig_termios, &new_termios)) < 0)
    //     return (-1);
    // if (signal(SIGPIPE, signal_callback_handler) == SIG_ERR)
    //     printf("\ncan't catch SIGWINCH\n");


    success = 0;
    copy_env = copy_environ((char **)environ);
	table_bins = ft_create_table_bins(copy_env);
    if (argc > 1 || isatty(0) == 0)
    {
        fd = isatty(0) == 0 ? 0 : open(argv[1], O_RDONLY);
        while (ft_get_cmd(fd, &command) != 0)
        {
            root = ft_parse_cmd(command);
    		execute_tree(*root, get_paths(copy_env), &copy_env,  0, 1, 2, &success);
	    }
    }
    else
    {
        while (42)
        {
			ft_putstr_fd("$> ", 0);
            ft_get_cmd(0, &command);
            root = ft_parse_cmd(command);
    		execute_tree(*root, get_paths(copy_env), &copy_env,  0, 1, 2, &success);
        }
    }
    return (success);
}
