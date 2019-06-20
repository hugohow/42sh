/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:10:24 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/20 16:12:05 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int shell_file(t_env ***p_copy_env, char **argv)
{
	char *command;
	t_node **root;
	int success;
	int fds[3];
	int fd;

	fds[0] = 0;
	fds[1] = 1;
	fds[2] = 2;
	success = 0;
	fd = ft_isatty(0) == 0 ? 0 : open(argv[1], O_RDONLY);
	while (get_next_line(fd, &command) != 0)
	{
		root = ft_parse_cmd(command, *p_copy_env);
		if (root)
			execute_tree(*root, p_copy_env,  fds, &success);
		ft_memdel((void **)&command);
	}
	return (success);
}
