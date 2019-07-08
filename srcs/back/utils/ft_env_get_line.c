/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:34:25 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 17:39:32 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_env_get_value(t_env **cpy_environ, char *key)
{
	size_t i;

	i = 0;
	while (cpy_environ[i])
	{
		if (ft_env_cmp_prefix(key, cpy_environ[i]->line) == 0)
		{
			if (ft_strlen(cpy_environ[i]->line + ft_strlen(key) + 1) == 0)
				return (NULL);
			return (cpy_environ[i]->line + ft_strlen(key) + 1);
		}
		i++;
	}
	return (NULL);
}

char	*ft_env_get_value_n(t_env **cpy_environ, char *key, size_t n)
{
	size_t	i;
	size_t	j;
	char	*line_i;

	i = 0;
	while (cpy_environ[i])
	{
		line_i = (cpy_environ[i])->line;
		if (line_i && ft_toupper(line_i[0]) == ft_toupper(key[0]))
		{
			j = 0;
			while (key[j] && line_i[j] &&\
				ft_toupper(line_i[j]) == ft_toupper(key[j]))
				j++;
			if (j == n && line_i[j] == '=')
			{
				if (line_i[j + 1] == 0)
					return (NULL);
				return (line_i + j + 1);
			}
		}
		i++;
	}
	return (NULL);
}

char	*ft_env_get_line(t_env **cpy_environ, char *prefix)
{
	size_t i;

	i = 0;
	while (cpy_environ[i])
	{
		if (ft_env_cmp_prefix(prefix, cpy_environ[i]->line) == 0)
			return (cpy_environ[i]->line);
		i++;
	}
	return (NULL);
}

char	*ft_env_get_line_n(t_env **cpy_environ, char *line, size_t n)
{
	size_t	i;
	size_t	j;
	char	*line_i;

	i = 0;
	while (cpy_environ[i])
	{
		line_i = (cpy_environ[i])->line;
		if (line_i && ft_toupper(line_i[0]) == ft_toupper(line[0]))
		{
			j = 0;
			while (line[j] && line_i[j] &&\
				ft_toupper(line_i[j]) == ft_toupper(line[j]))
				j++;
			if (j == n && line_i[j] == '=')
				return (line_i);
		}
		i++;
	}
	return (NULL);
}
