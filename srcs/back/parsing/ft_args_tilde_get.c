/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_tilde_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:46:29 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/13 16:48:22 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	is_separator(char c)
{
	if (c == '/' || c == ':')
		return (1);
	return (0);
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

static int	is_tilde_prefix(char *str, int i)
{
	if (str[i] == '~' && (i == 0 ||\
		(i > 1 && str[i - 1] == '=' && ft_isalpha(str[i - 2]))))
		return (1);
	return (0);
}

char		*ft_args_tilde_get(char *str, t_env **copy_env)
{
	int		i;
	char	*tmp;

	i = -1;
	if (str == NULL)
		return (NULL);
	while (str[++i])
	{
		if (is_tilde_prefix(str, i))
		{
			if (str[i + 1] == '~')
				i++;
			else if ((tmp = ft_is_tilde_user(str + i + 1)))
				str = ft_replace_by_home_login(str, i, tmp);
			else if (str[i + 1] == 0 || is_separator(str[i + 1]))
				str = ft_replace_by_home(str, i, copy_env);
			else if (str[i + 1] == '-' && (str[i + 2] == 0 \
				|| is_separator(str[i + 2])))
				str = ft_replace_by_oldpwd(str, i, copy_env);
			else if (str[i + 1] == '+' && (str[i + 2] == 0 \
				|| is_separator(str[i + 2])))
				str = ft_replace_by_pwd(str, i, copy_env);
		}
	}
	return (str);
}
