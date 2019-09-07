/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interactive_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaint- <kesaint-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 23:08:39 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/09/07 18:55:51 by kesaint-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Init temrcaps config
*/

static t_config	get_new_config(t_config old_config)
{
	t_config new_config;

	new_config = old_config;
	new_config.c_iflag &= \
		~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	new_config.c_oflag &= ~OPOST;
	new_config.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	new_config.c_cflag &= ~(CSIZE | PARENB);
	new_config.c_cflag |= CS8;
	return (new_config);
}

static int		handle_errors(t_env **copy_env)
{
	int		ret;
	char	*term_name;

	if ((term_name = ft_env_get_value(copy_env, "TERM")))
		ret = tgetent(NULL, term_name);
	else
		ret = tgetent(NULL, "xterm-256color");
	if (ret == -1)
	{
		ft_putstr_fd("Could not access to the termcap database..\n",\
			STDERR_FILENO);
		return (-1);
	}
	else if (ret == 0)
	{
		ft_putstr_fd(\
			"Terminal type '%s' is not defined in termcap database.\n",\
				STDERR_FILENO);
		ft_putstr_fd(term_name, STDERR_FILENO);
		return (-1);
	}
	return (ret);
}

int				ft_interactive_init(void)
{
	t_env	**copy_env;
	int		ret;
	t_vars	*p_vars;

	p_vars = ft_vars_get();
	copy_env = ft_vars_get_copy_env();
	if ((ret = handle_errors(copy_env)) < 0)
	{
		ft_putstr_fd("Init termcaps failed\n", 2);
		return (-1);
	}
	tcgetattr(STDIN_FILENO, &(p_vars->old_config));
	p_vars->new_config = get_new_config(p_vars->old_config);
	tcsetattr(0, TCSAFLUSH, &(p_vars->new_config));
	return (0);
}
