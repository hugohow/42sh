/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_dollar_replace_expansion.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:04:27 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/05 17:26:38 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int ft_args_resolve_expansion_special(char *expansion, char **p_output)
{
	size_t len_expansion;
	t_vars 	*p_vars;
	int nb;

	p_vars = ft_vars_get();
	len_expansion = 1;
	if (ft_strncmp(expansion, "?", len_expansion) == 0)
		*p_output = ft_itoa(p_vars->success_exit);
	if (ft_strncmp(expansion, "$", len_expansion) == 0)
		*p_output = ft_itoa(p_vars->pid);
	if (ft_strncmp(expansion, "#", len_expansion) == 0)
		*p_output = ft_itoa(p_vars->argc);
	if (ft_isdigit(expansion[0]))
	{
		nb = expansion[0] - '0';
		if (nb < p_vars->argc)
			*p_output = ft_strdup(p_vars->argv_list[nb]);
		else
			*p_output = ft_strdup("");
	}
	if (*p_output)
		return (0);
	return (1);
}


/*
** get value of ${PATH} 
*/


static char *ft_args_resolve_expansion(char *str, int start, int end, t_env **copy_env)
{
	char *line;
	char *expansion;
	char *output;
	size_t len_expansion;

	output = NULL;
	start++;
	if (str[start] == '{')
	{
		start++;
		end--;
	}
	expansion = str + start;
	len_expansion = end - start;
	if (len_expansion == 1)
	{
		if (ft_args_resolve_expansion_special(expansion, &output) == 0)
			return (output);
	}
	line = ft_env_get_value_n(copy_env, expansion, len_expansion);
	return (ft_strdup(line));
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
	expansion = ft_args_resolve_expansion(str, start, end, copy_env);
	if (expansion == NULL)
		expansion = ft_strdup("");
	to_free = str;
	str[start] = 0;
	str = ft_strjoin_(str, expansion, str + end);
	ft_memdel((void **)&to_free);
	ft_memdel((void **)&expansion);
	return (str);
}
