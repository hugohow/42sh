/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_tilde_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:46:29 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/11 22:26:17 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int is_separator(char c)
{
	if (c == '/' || c == ':')
		return (1);
	return (0);
}

/*
** ~root/ -> ${HOME_ROOT}/
*/

static char	*ft_replace_by_home_login(char *str, int i, char *login)
{
	char *to_free;
	char *line;
	struct passwd	*pw;
	int j;

	line = NULL;
	if (((pw = getpwnam(login))))
		line = pw->pw_dir;
	if (line)
	{
		to_free = str;
		j = ft_strlen(login) + 1;
		str[i] = 0;
		if (is_separator(str[i + j]))
			str = ft_strjoin_(str, line, str + i + j);
		else
			str = ft_strjoin(str, line);
		ft_memdel((void **)&to_free);
	}
	return (str);
}

/*
** ~/ -> ${HOME}/
*/

static char	*ft_replace_by_home(char *str, int i, t_env **copy_env)
{
	char *to_free;
	char *line;
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

static char	*ft_replace_by_oldpwd(char *str, int i, t_env **copy_env)
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

static char	*ft_replace_by_pwd(char *str, int i, t_env **copy_env)
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

static char	*ft_is_tilde_user(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	if (str[i] == 0 || is_separator(str[i]))
	{
		if (i > 0)
		{
			return ((ft_strsub(str, 0, i)));
		}
	}
	return (NULL);
}

char		*ft_args_tilde_get(char *str, t_env **copy_env)
{
	int i;
	char	*tmp;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '~' && (i == 0 || (i > 1 && str[i - 1] == '=' && ft_isalpha(str[i - 2]))))
		{
			if (str[i + 1] == '~')
				i++;
			else if ((tmp = ft_is_tilde_user(str + i + 1)))
			{
				str = ft_replace_by_home_login(str, i, tmp);
				ft_memdel((void **)&tmp);
			}
			else if (str[i + 1] == 0 || is_separator(str[i + 1]))
				str = ft_replace_by_home(str, i, copy_env);
			else if (str[i + 1] == '-' && (str[i + 2] == 0 \
				|| is_separator(str[i + 2])))
				str = ft_replace_by_oldpwd(str, i, copy_env);
			else if (str[i + 1] == '+' && (str[i + 2] == 0 \
				|| is_separator(str[i + 2])))
				str = ft_replace_by_pwd(str, i, copy_env);
		}
		i++;
	}
	return (str);
}
