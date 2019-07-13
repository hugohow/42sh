/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:58:20 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/13 16:38:51 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Builtin to get the environnement of the process
*/

void			ft_print_env(t_env **cpy_env, int fds[])
{
	int i;

	i = 0;
	while (cpy_env[i])
	{
		ft_putstr_fd(cpy_env[i]->line, fds[1]);
		ft_putstr_fd("\n", fds[1]);
		i++;
	}
}

t_env			**clear_environ(void)
{
	t_env **output;

	if (!(output = (t_env **)ft_memalloc((sizeof(t_env *) + 1))))
		return (NULL);
	return (output);
}

static t_env	**ft_get_env(int flag, t_env **cpy_environ, int fds[])
{
	t_env **copy_env;

	if (flag == FLAG_ENV_I)
		copy_env = clear_environ();
	else
		copy_env = ft_env_deep_copy(cpy_environ);
	if (copy_env == NULL)
	{
		ft_putstr_fd("Error copy env", fds[2]);
		return (NULL);
	}
	return (copy_env);
}

int				ft_env(char **argv, t_env **cpy_environ, int fds[])
{
	int		flag;
	int		res;
	t_env	**copy_env;
	t_ht	**p_hash;

	if (ft_list_size(++argv) == 0)
	{
		ft_print_env(cpy_environ, fds);
		return (0);
	}
	if ((flag = ft_env_parse(&argv, fds)) < 0)
		return (1);
	if (!(copy_env = ft_get_env(flag, cpy_environ, fds)))
		return (1);
	if (!(p_hash = (t_ht **)ft_memalloc(sizeof(t_ht *))))
	{
		ft_env_free(&copy_env);
		return (1);
	}
	argv = ft_env_complete_env(argv, &copy_env, p_hash);
	res = ft_env_cmd_exec(argv, p_hash, &copy_env, fds);
	ft_env_free(&copy_env);
	ft_ht_free(p_hash);
	ft_memdel((void **)&(p_hash));
	return (res);
}
