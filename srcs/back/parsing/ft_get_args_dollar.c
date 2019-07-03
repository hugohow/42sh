/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 13:42:37 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/03 16:53:30 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


static int	ft_is_special_param(char c)
{
	if (c == '*' || c == '@' || c == '#' || c == '?'|| c == '-' || c == '$' || c == '!')
		return (1);
	return (0);
}

/*
** lenght of {PATH} or $@
*/

static int get_expansion_length(char *str)
{
	int ret;

	ret = 1;
	if (str[ret] == 0)
		return (0);
	if (str[ret] == '{')
	{
		ret++;
		if (ft_isdigit(str[ret]) && str[ret] != '}')
		{
			ft_dprintf(2, "minishell: bad substitution\n");
			return (-1);
		}
		while (str[ret] && str[ret] != '}')
		{
			if (ft_is_special_param(str[ret]) && ret != 2)
			{
				ft_dprintf(2, "minishell: bad substitution\n");
				return (-1);
			}
			if (ft_is_special_param(str[ret]) == 0 && ft_isalnum(str[ret]) == 0 && str[ret] != '_')
			{
				ft_dprintf(2, "minishell: bad substitution\n");
				return (-1);
			}
			ret++;
		}
		if (str[ret] == 0)
		{
			ft_dprintf(2, "minishell: bad substitution\n");
			return (-1);
		}
		ret++;
	}
	else
	{
		if (ft_isdigit(str[ret]))
			return (ret + 1);
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

static char *replace_expansion(char *str, int i, int ret, t_env **copy_env)
{
	char *tmp;
	char *expansion;
	int start;
	int end;

	start = i;
	end = i + ret;
	expansion = resolve_expansion(str, start, end, copy_env);
	tmp = ft_strjoin(expansion, str + end);
	str[start] = 0;
	str = ft_strjoin_free_first(str, tmp);
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&expansion);
	return (str);
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
				ft_memdel((void **)&str);
				return (NULL);
			}
			if (ret != 0)
				str = replace_expansion(str, i, ret, copy_env);
		}
		i++;
	}
	if (ft_strlen(str) == 0)
	{
		ft_memdel((void **)&str);
		return (ft_strdup(""));
	}
	return (str);
}