/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_tild_replace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 13:04:42 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/13 18:45:00 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	is_separator(char c)
{
	if (c == '/' || c == ':')
		return (1);
	return (0);
}

/*
** ~root/ -> ${HOME_ROOT}/
*/

char		*ft_replace_by_home_login(char *str, int i, char *login)
{
	char			*to_free;
	int				j;

	to_free = str;
	j = ft_strlen(login) + 1;
	str[i] = 0;
	if (is_separator(str[i + j]))
		str = ft_strjoin_(str, login, str + i + j);
	else
		str = ft_strjoin(str, login);
	ft_memdel((void **)&to_free);
	ft_memdel((void **)&login);
	return (str);
}

/*
** ~/ -> ${HOME}/
*/

char		*ft_replace_by_home(char *str, int i, t_env **copy_env)
{
	char			*to_free;
	char			*line;
	struct passwd	*pw;

	to_free = NULL;
	line = ft_env_get_value(copy_env, "HOME");
	if (line == NULL)
	{
		pw = getpwnam(getlogin());
		if (pw)
			line = pw->pw_dir;
	}
	if (line)
	{
		to_free = str;
		str[i] = 0;
		if (is_separator(str[i + 1]))
			str = ft_strjoin_(str, line, str + i + 1);
		else
			str = ft_strjoin(str, line);
		ft_memdel((void **)&to_free);
	}
	return (str);
}

/*
** ~-/ -> ${OLDPWD}/
*/

char		*ft_replace_by_oldpwd(char *str, int i, t_env **copy_env)
{
	char	*to_free;
	char	*line;

	to_free = NULL;
	line = ft_env_get_value(copy_env, "OLDPWD");
	if (line)
	{
		to_free = str;
		str[i] = 0;
		str[i + 1] = 0;
		if (is_separator(str[i + 2]))
			str = ft_strjoin_(str, "$OLDPWD", str + i + 2);
		else if (str[i + 2] == 0)
			str = ft_strjoin(str, "$OLDPWD");
		ft_memdel((void **)&to_free);
	}
	return (str);
}

/*
** ~+/ -> ${PWD}/
*/

char		*ft_replace_by_pwd(char *str, int i, t_env **copy_env)
{
	char	*to_free;
	char	*line;

	to_free = NULL;
	line = ft_env_get_value(copy_env, "PWD");
	if (line)
	{
		to_free = str;
		str[i] = 0;
		str[i + 1] = 0;
		if (is_separator(str[i + 2]))
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
