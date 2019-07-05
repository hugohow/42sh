/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_tilde_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:46:29 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/05 15:47:32 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ~/ -> ${HOME}/
*/

static char *ft_replace_by_home(char *str, int i, t_env **copy_env)
{
	char *to_free;
	char *line;

	to_free = NULL;
	line = ft_env_get_value(copy_env, "HOME");
	if (line)
	{
		to_free = str;
		str[i] = 0;
		if (str[i + 1] == '/')
		{
			str = ft_strjoin_(str, "$HOME", str + i + 1);
		}
		else if (str[i + 1] == 0)
		{
			str = ft_strjoin(str, "$HOME");	
		}
		ft_memdel((void **)&to_free);

	}
	return (str);
}

/*
** ~-/ -> ${OLDPWD}/
*/

static char *ft_replace_by_oldpwd(char *str, int i, t_env **copy_env)
{
	char *to_free;
	char *line;

	to_free = NULL;
	line = ft_env_get_value(copy_env, "OLDPWD");
	if (line)
	{
		to_free = str;
		str[i] = 0;
		str[i + 1] = 0;
		if (str[i + 2] == '/')
		{
			str = ft_strjoin_(str, "$OLDPWD", str + i + 2);
		}
		else if (str[i + 2] == 0)
		{
			str = ft_strjoin(str, "$OLDPWD");
		}
		ft_memdel((void **)&to_free);
	}
	return (str);
}

/*
** ~+/ -> ${PWD}/
*/

static char *ft_replace_by_pwd(char *str, int i, t_env **copy_env)
{
	char *to_free;
	char *line;

	to_free = NULL;
	line = ft_env_get_value(copy_env, "PWD");
	if (line)
	{
		to_free = str;
		str[i] = 0;
		str[i + 1] = 0;
		if (str[i + 2] == '/')
		{
			str = ft_strjoin_(str, "$PWD", str + i + 2);
		}
		else if (str[i + 2] == 0)
		{
			str = ft_strjoin(str, "$PWD");
		}
		ft_memdel((void **)&to_free);
	}
	return (str);
}


char *ft_args_tilde_get(char *str, t_env **copy_env)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '~' && (i == 0 || str[i - 1] == '='))
		{
			if (str[i + 1] == '~')
				i++;
			else if (str[i + 1] == 0 || str[i + 1] == '/')
				str = ft_replace_by_home(str, i , copy_env);
			else if (str[i + 1] == '-' && (str[i + 2] == 0 || str[i + 2] == '/'))
				str = ft_replace_by_oldpwd(str, i , copy_env);
			else if (str[i + 1] == '+' && (str[i + 2] == 0 || str[i + 2] == '/'))
				str = ft_replace_by_pwd(str, i , copy_env);
		}
		i++;
	}


	return (str);
}