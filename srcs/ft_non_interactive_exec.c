/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_non_interactive_exec.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 22:25:42 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/03 23:40:30 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_non_interactive_exec(char **argv)
{
	char *command;
	int success;
	int fds[3];
	int fd;
	int end;
	t_env ***p_copy_env;

	p_copy_env = ft_vars_get_p_copy_env();
	fds[0] = 0;
	fds[1] = 1;
	fds[2] = 2;
	success = 0;
	fd = ft_isatty(0) == 0 ? 0 : open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_env_free(p_copy_env);
		ft_dprintf(fds[2], "shell: %s: No such file or directory\n", argv[1]);
		exit(EXIT_UTILITY_NOT_FOUND);
	}
	end = 0;
	while (42)
	{
		end = ft_stdin_get_cmd(fd, &command, *p_copy_env);
		ft_cmd_exec(command, p_copy_env, fds, &success);
		if (*((int *)ft_vars_get_value(KEY_MUST_EXIT)) == 1)
			break ;
		if (end == 1)
			break;
	}
	if (fd != 0)
		close(fd);
	return (success);
}
