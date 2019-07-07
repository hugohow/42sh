/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 02:17:21 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/07 14:37:17 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_cmd_exec(char *command, t_env ***p_copy_env, t_ht **p_table_bins, int fds[])
{
	t_node *root;
	t_ht *hash_table;

	if (p_table_bins == NULL)
	{
		if (command == NULL)
			return ;
		hash_table = ft_bins_table_get();
		root = ft_syntax_tree_create(command, *p_copy_env);
		ft_syntax_tree_execute(root, p_copy_env, &hash_table, fds);
		ft_syntax_tree_free(&root);
		ft_memdel((void **)&command);
	}
	else
	{
		if (command == NULL)
			return ;
		root = ft_syntax_tree_create(command, *p_copy_env);
		ft_syntax_tree_execute(root, p_copy_env, p_table_bins, fds);
		ft_syntax_tree_free(&root);
		ft_memdel((void **)&command);
	}
}