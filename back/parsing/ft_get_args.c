/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:25:36 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/17 12:46:24 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


// ~
// The value of $HOME
// ~/foo
// $HOME/foo
// ~fred/foo
// The subdirectory foo of the home directory of the user fred
// ~+/foo
// $PWD/foo
// ~-/foo
// ${OLDPWD-'~-'}/foo
// ~N
// The string that would be displayed by ‘dirs +N’
// ~+N
// The string that would be displayed by ‘dirs +N’
// ~-N
// The string that would be displayed by ‘dirs -N’


char **ft_get_args(char *cmd, t_env **copy_env)
{

	char	**args;
	int		i;


	args = ft_strsplit(cmd, ' ');

	i = 0;
	if (copy_env)
	
	while (args[i])
	{
		args[i] = ft_get_args_dollar(args[i], copy_env);
		args[i] = ft_get_args_tilde(args[i], copy_env);
		// while (ft_strchr(args[i], '~'))
		// 	args[i] = ft_replace_tilde(args[i]);
		i++;
	}
	return (args);
}