/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_dollar_replace_expansion.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:04:27 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/04 16:21:00 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


/*
** get value of ${PATH} 
*/


static char *resolve_expansion(char *str, int start, int end, t_env **copy_env)
{
	char *line;
	char *expansion;
	size_t len_expansion;
	t_vars 	*p_vars;

	p_vars = ft_vars_get();
	start++;
	if (str[start] == '{')
	{
		expansion = str + start + 1;
		len_expansion = end - 2 - start;
		if (len_expansion == 1)
		{
			if (ft_strncmp(expansion, "?", len_expansion) == 0)
				return (ft_itoa(p_vars->success_exit));
			if (ft_strncmp(expansion, "$", len_expansion) == 0)
				return (ft_itoa(p_vars->pid));
			if (ft_strncmp(expansion, "#", len_expansion) == 0)
				return (ft_itoa(p_vars->argc));
			if (ft_isdigit(expansion[0]))
			{
				int nb;

				nb = expansion[0] - '0';
				if (nb < p_vars->argc)
					return (ft_strdup(p_vars->argv_list[nb]));
				else
					return (ft_strdup(""));
			}
		}
		line = ft_env_get_line_n(copy_env, expansion, len_expansion);
		if (line)
			return (ft_strdup(line + end - start - 1));
		else
			return (ft_strdup(""));
	}
	else
	{
		expansion = str + start;
		len_expansion = end - start;
		if (len_expansion == 1)
		{
			if (ft_strncmp(expansion, "?", len_expansion) == 0)
				return (ft_itoa(p_vars->success_exit));
			if (ft_strncmp(expansion, "$", len_expansion) == 0)
				return (ft_itoa(p_vars->pid));
			if (ft_strncmp(expansion, "#", len_expansion) == 0)
				return (ft_itoa(p_vars->argc));
			if (ft_isdigit(expansion[0]))
			{
				int nb;

				nb = expansion[0] - '0';
				if (nb < p_vars->argc)
					return (ft_strdup(p_vars->argv_list[nb]));
				else
					return (ft_strdup(""));
			}
		}
		line = ft_env_get_line_n(copy_env, expansion, len_expansion);
		if (line)
			return (ft_strdup(line + end - start + 1));
		else
			return (ft_strdup(""));
	}
}


/*
** replace ${PATH}
*/

char *ft_args_dollar_replace_expansion(char *str, int i, int ret, t_env **copy_env)
{
	char *expansion;
	char *to_free;
	int start;
	int end;

	start = i;
	end = i + ret;
	expansion = resolve_expansion(str, start, end, copy_env);

	to_free = str;
	str[start] = 0;
	str = ft_strjoin_(str, expansion, str + end);
	ft_memdel((void **)&to_free);
	ft_memdel((void **)&expansion);
	return (str);
}
