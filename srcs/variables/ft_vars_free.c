/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 00:15:54 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/11 17:09:45 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_vars_free(void)
{
	t_vars	*p_vars;

	p_vars = ft_vars_get();
	if (p_vars)
	{
		if (p_vars->copy_env)
			ft_env_free(&(p_vars->copy_env));
		if (p_vars->cwd)
			ft_memdel((void **)&(p_vars->cwd));
		if (p_vars->p_hash_table)
		{
			ft_ht_free(p_vars->p_hash_table);
			ft_memdel((void **)&(p_vars->p_hash_table));
		}
		if (p_vars->path_default)
			ft_memdel((void **)&(p_vars->path_default));
		if (p_vars->cmd)
		{
			ft_lstfree((p_vars->cmd)->head);
			ft_memdel((void **)&(p_vars->cmd));
		}
		ft_memdel((void **)&p_vars);
	}
}
