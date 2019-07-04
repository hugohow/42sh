/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interactive_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 23:08:39 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/04 16:35:01 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Init temrcaps config
*/

static struct termios get_new_config(struct termios old_config)
{
	struct termios new_config;

	new_config = old_config;
    new_config.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    new_config.c_oflag &= ~OPOST;
    new_config.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    new_config.c_cflag &= ~(CSIZE | PARENB);
    new_config.c_cflag |= CS8;
	return (new_config);
}


int ft_interactive_init(void)
{
	t_env **copy_env;
    char *term_name;
    int ret;
	t_vars 	*p_vars;

	p_vars = ft_vars_get();
	copy_env = ft_vars_get_copy_env();
    if ((term_name = ft_env_get_value(copy_env, "TERM")))
		ret = tgetent(NULL, term_name);
	else
		ret = tgetent(NULL, "xterm-256color");
    if (ret == -1)
    {
        ft_putstr_fd("Could not access to the termcap database..\n", STDERR_FILENO);
        return (-1);
    }
    else if (ret == 0)
    {
        ft_putstr_fd("Terminal type '%s' is not defined in termcap database (or have too few informations).\n", STDERR_FILENO);
		ft_putstr_fd(term_name, STDERR_FILENO);
        return (-1);
    }
	tcgetattr(STDIN_FILENO, &(p_vars->old_config));
    p_vars->new_config = get_new_config(p_vars->old_config);
  	tcsetattr(0, TCSAFLUSH, &(p_vars->new_config));
    return (0);
}
