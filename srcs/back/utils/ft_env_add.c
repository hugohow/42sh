/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:00:28 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/09 14:55:36 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		ft_env_size(t_env **list)
{
	int size;

	size = 0;
	if (list == NULL)
		return (-1);
	while (list[size])
		size++;
	return (size);
}

static t_env	*ft_new_env(char *env_line)
{
	t_env *new_env;

	if (!(new_env = (t_env *)ft_memalloc(sizeof(t_env))))
		return (NULL);
	new_env->line = env_line;
	return (new_env);
}

void			ft_env_add(char *prefix, char *value, t_env ***p_environ)
{
	t_env	**new_environ;
	t_env	**old_env;
	char	*env_line;
	int		i;

	new_environ = NULL;
	if (value == NULL || prefix == NULL)
		return ;
	env_line = ft_strjoin_(prefix, "=", value);
	old_env = *p_environ;
	if (ft_env_change_line(prefix, env_line, old_env) == 0)
	{
		if (!(new_environ = (t_env **)ft_memalloc((ft_env_size(old_env)\
			+ 2) * sizeof(t_env *))))
			return ;
		i = -1;
		while (++i < ft_env_size(old_env))
			new_environ[i] = (old_env)[i];
		new_environ[i] = ft_new_env(env_line);
		if (new_environ[i])
			new_environ[i + 1] = 0;
		ft_memdel((void **)&old_env);
		*p_environ = new_environ;
	}
}
