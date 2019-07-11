/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_non_interactive_exec.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 22:25:42 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/11 17:46:55 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		signal_callback_handler_non_interactive(int signum)
{
	(void)signum;
}

static void	init_exec_fds(int *p_fd, int fds[], char **argv)
{
	fds[0] = 0;
	fds[1] = 1;
	fds[2] = 2;
	*p_fd = ft_isatty(0) == 0 ? 0 : open(argv[1], O_RDONLY);
	if (*p_fd < 0)
	{
		ft_vars_free();
		ft_dprintf(fds[2], "shell: %s: No such file or directory\n", argv[1]);
		exit(EXIT_UTILITY_NOT_FOUND);
	}
	if (signal(SIGINT, signal_callback_handler_non_interactive) == SIG_ERR)
		ft_putstr_fd("can't catch SIGINT\n", 2);
	if (signal(SIGTSTP, signal_callback_handler_non_interactive) == SIG_ERR)
		ft_putstr_fd("can't catch SIGTSTP\n", 2);
	if (signal(SIGTERM, signal_callback_handler_non_interactive) == SIG_ERR)
		ft_putstr_fd("can't catch SIGTERM\n", 2);
	if (signal(SIGQUIT, signal_callback_handler_non_interactive) == SIG_ERR)
		ft_putstr_fd("can't catch SIGQUIT\n", 2);
}

int			ft_non_interactive_exec(char **argv)
{
	char	*command;
	int		fds[3];
	int		fd;
	int		ret;
	t_env	***p_copy_env;

	p_copy_env = ft_vars_get_p_copy_env();
	init_exec_fds(&fd, fds, argv);
	while (42)
	{
		ret = ft_non_interactive_get_cmd(fd, &command);
		ft_cmd_exec(command, p_copy_env, NULL, fds);
		if (ret == 0)
			break ;
		if (*((int *)ft_vars_get_value(KEY_MUST_EXIT)) == 1)
			break ;
		if (*((int *)ft_vars_get_value(KEY_LAST_KEY)) == 0)
			break ;
	}
	if (fd != 0)
		close(fd);
	return (0);
}
