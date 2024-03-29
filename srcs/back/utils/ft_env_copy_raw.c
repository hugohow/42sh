/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_copy_raw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:12:28 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/13 12:36:14 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_get_bins_table(t_env **copy)
{
	t_vars	*p_vars;
	char	*value;

	p_vars = ft_vars_get();
	if (!(p_vars->p_hash_table = (t_ht **)ft_memalloc((sizeof(t_ht *)))))
		return ;
	if ((value = ft_env_get_line(copy, "PATH")))
		*(p_vars->p_hash_table) = ft_bins_table_create(value);
	else
	{
		p_vars->path_default = ft_strdup(DEFAULT_PATH);
		*(p_vars->p_hash_table) = ft_bins_table_create(DEFAULT_PATH);
	}
}

t_env		**ft_env_copy_raw(char **str, char **argv)
{
	t_env	**copy;
	int		i;

	(void)argv;
	i = 0;
	while (str[i])
		i++;
	if (!(copy = (t_env **)ft_memalloc((i + 10) * sizeof(t_env *))))
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (!(copy[i] = (t_env *)ft_memalloc(sizeof(t_env))))
			return (ft_env_copy_exit(copy));
		copy[i]->line = ft_strdup(str[i]);
	}
	copy[i] = 0;
	if (ft_env_get_line(copy, "SHLVL") == NULL)
		copy = ft_env_add_default_shlvl(copy);
	if (ft_env_get_line(copy, "PWD") == NULL)
		copy = ft_env_add_default_pwd(copy);
	copy = ft_env_increment_shlvl(copy);
	ft_get_bins_table(copy);
	return (copy);
}
