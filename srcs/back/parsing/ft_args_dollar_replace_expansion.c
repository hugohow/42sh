/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_dollar_replace_expansion.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:04:27 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/13 16:44:21 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*ft_search_local_variable(char *key, size_t n)
{
	t_vars	*p_vars;

	p_vars = ft_vars_get();
	if (ft_strncmp(key, "PATH", n) == 0)
		return (p_vars->path_default);
	return (NULL);
}

static int	ft_args_resolve_expansion_special(char *expansion, char **p_output)
{
	size_t	len_expansion;
	t_vars	*p_vars;
	int		nb;

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

static char	*ft_args_resolve_expansion(char *str,\
	int start, int end, t_env **c_env)
{
	char	*line;
	char	*expansion;
	char	*output;
	size_t	len_expansion;

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
	if (!(line = ft_env_get_value_n(c_env, expansion, len_expansion)))
	{
		if (!(line = ft_search_local_variable(expansion, len_expansion)))
			return (ft_strdup(""));
	}
	return (ft_strdup(line));
}

/*
** replace ${PATH}
*/

char		*ft_args_dollar_replace_expansion(char *str, int i,\
	int ret, t_env **c_env)
{
	char *expansion;
	char *output;
	char *prefix;
	char *suffix;

	expansion = ft_args_resolve_expansion(str, i, i + ret, c_env);
	if (expansion == NULL)
		expansion = ft_strdup("");
	prefix = ft_strsub(str, 0, i);
	if (prefix == NULL)
		prefix = ft_strdup("");
	suffix = ft_strsub(str, (i + ret), ft_strlen(str) - (i + ret));
	if (suffix == NULL)
		suffix = ft_strdup("");
	output = ft_strjoin_(prefix, expansion, suffix);
	ft_memdel((void **)&prefix);
	ft_memdel((void **)&suffix);
	ft_memdel((void **)&expansion);
	return (output);
}
