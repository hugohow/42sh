/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 13:42:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/25 01:42:04 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


static int	ft_is_special_param(char c)
{
	if (c == '*' || c == '@' || c == '#' || c == '?'|| c == '-' || c == '$' || c == '!')
		return (1);
	return (0);
}

static int get_expansion_length(char *str)
{
	int ret;

	ret = 1;
	if (str[ret] == 0)
		return (0);
	if (str[ret] == '{')
	{
		ret++;
		while (str[ret] && str[ret] != '}')
		{
			if (ft_is_special_param(str[ret]) && ret != 2)
				return (-1);
			if (ft_is_special_param(str[ret]) == 0 && ft_isalnum(str[ret]) == 0 && str[ret] != '_')
				return (-1);
			ret++;
		}
		if (str[ret] == 0)
			return (-1);
		ret++;
	}
	else
	{
		while (str[ret] && str[ret] != '/')
		{
			if (ft_is_special_param(str[ret]))
			{
				if (ret == 1)
					ret++;
				break;
			}
			else if (ft_isalnum(str[ret]) == 0 && str[ret] != '_')
				break ;
			ret++;
		}
	}
	return (ret);
}

static const char *resolve_expansion(char *str, int start, int end, t_env **copy_env)
{
	const char *line;

	// print_n(str, i, j);

	start++;

	if (str[start] == '{')
	{
		line = ft_env_get_line_n(copy_env, str + start + 1, end - 2 - start);
		// print_n(str + i + 1, 0, j - 2 - i);
		if (line)
			return (line + end - start - 1);
		else
			return ("");
	}
	else
	{
		line = ft_env_get_line_n(copy_env, str + start, end - start);
		if (line)
			return (line + end - start + 1);
		else
			return ("");
	}
}



char *ft_get_args_dollar(char *str, t_env **copy_env, int *p_result_parsing)
{
	int i;
	int ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			ret = get_expansion_length(str + i);
			if (ret == -1)
			{
				*p_result_parsing = 1;
				ft_putstr_fd("bad substitution\n", 2);
				return (NULL);
			}
			if (ret != 0)
			{
				char *tmp;
				char *to_free;

				to_free = str;
				tmp = ft_strjoin(resolve_expansion(str, i, i + ret, copy_env), str + i + ret);
				str[i] = 0;
				str = ft_strjoin(str, tmp);
				ft_memdel((void **)&tmp);
				ft_memdel((void **)&to_free);
			}
		}
		i += 1;
	}
	if (ft_strlen(str) == 0)
		return (ft_strdup(""));
	return (str);
}