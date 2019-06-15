/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:25:36 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/15 20:34:08 by hhow-cho         ###   ########.fr       */
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


static char *ft_replace_dollar(char *str, char **copy_env)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			size_t len;

			len = 0;
			i++;
			while (str[i + len] && ft_isalpha(str[i + len]))
				len++;
			if (len != 0)
			{
				str[i - 1] = ' ';
				char *line;

				line = ft_get_line_env_n(copy_env, str + i, len);
				if (line)
				{
					char *tmp;
					str[i - 1] = 0;
					tmp = ft_strjoin(str, line + len + 1);
					str = ft_strjoin(tmp, str + i + len);
					
					// printf("line env: %s\n", line + len + 1);
				}
			}
			else
			{
			
			}
		}
		i++;
	}
	return (str);
}

char **ft_get_args(char *cmd, char **copy_env)
{

	char	**args;
	int		i;


	args = ft_strsplit(cmd, ' ');

	i = 0;
	if (copy_env)
	
	while (args[i])
	{
		args[i] = ft_replace_dollar(args[i], copy_env);
		// while (ft_strchr(args[i], '~'))
		// 	args[i] = ft_replace_tilde(args[i]);
		i++;
	}
	return (args);
}