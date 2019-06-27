/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args_tilde.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:46:29 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/27 21:22:58 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ~/ -> ${HOME}/
*/

static char *ft_replace_by_home(char *str, int i, char *line)
{
	char *to_free;

	to_free = NULL;
	if (line)
	{
		str[i] = 0;
		if (str[i + 1] == '/')
		{
			to_free = ft_strjoin(line, str + i + 1);
		}
		else if (str[i + 1] == 0)
		{
			to_free = ft_strdup(line);
		}
		str = ft_strjoin_free_first(str, to_free);
		ft_memdel((void **)&to_free);
	}
	return (str);
}

/*
** ~-/ -> ${OLDPWD}/
*/

static char *ft_replace_by_oldpwd(char *str, int i, char *line)
{
	char *to_free;

	to_free = NULL;
	if (line)
	{
		str[i] = 0;
		str[i + 1] = 0;
		if (str[i + 2] == '/')
		{
			to_free = ft_strjoin(line, str + i + 2);
		}
		else if (str[i + 2] == 0)
		{
			to_free = ft_strdup(line);
		}
		str = ft_strjoin_free_first(str, to_free);
		ft_memdel((void **)&to_free);
	}
	return (str);
}

/*
** ~+/ -> ${PWD}/
*/

static char *ft_replace_by_pwd(char *str, int i, char *line)
{
	char *to_free;

	to_free = NULL;
	if (line)
	{
		str[i] = 0;
		str[i + 1] = 0;
		if (str[i + 2] == '/')
		{
			to_free = ft_strjoin(line, str + i + 2);
		}
		else if (str[i + 2] == 0)
		{
			to_free = ft_strdup(line);
		}
		str = ft_strjoin_free_first(str, to_free);
		ft_memdel((void **)&to_free);
	}
	return (str);
}


char *ft_get_args_tilde(char *str, t_env **copy_env)
{
	char *line;
	int i;

	i = 0;
	while (str[i])
	{
		// je ne comprends pas poutquoi y'a pas ':' comme indiqué dans la doc
		if (str[i] == '~' && (i == 0 || str[i - 1] == '='))
		{
			if (str[i + 1] == '~')
			{
				i++;
			}
			else if (str[i + 1] == 0 || str[i + 1] == '/')
			{
				line = ft_env_get_value(copy_env, "HOME");
				if (line)
				{
					str = ft_replace_by_home(str, i , line);
					return (ft_get_args_tilde(str, copy_env));
				}
			}
			else if (str[i + 1] == '-' && (str[i + 2] == 0 || str[i + 2] == '/'))
			{
				line = ft_env_get_value(copy_env, "OLDPWD");
				if (line)
				{
					str = ft_replace_by_oldpwd(str, i , line);
					return (ft_get_args_tilde(str, copy_env));
				}
			}
			else if (str[i + 1] == '+' && (str[i + 2] == 0 || str[i + 2] == '/'))
			{
				line = ft_env_get_value(copy_env, "PWD");
				if (line)
				{
					str = ft_replace_by_pwd(str, i , line);
					return (ft_get_args_tilde(str, copy_env));
				}
			}
		}
		i++;
	}


	return (str);
}