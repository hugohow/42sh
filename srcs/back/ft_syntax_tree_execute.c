/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_tree_execute.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:24:52 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/07 14:28:43 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    ft_syntax_tree_execute(t_node *node, t_env ***p_environ, t_ht **p_table_bins, int fds[])
{
	int k;
    int success;

	if (node == NULL)
		return ;
    if (node && node->type & TYPE_CMD)
    {
		success = ft_exe_bin(node, p_environ, p_table_bins, fds);
		*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)) = success;
    }
	k = 0;
    if (node && node->child && node->child[k])
    {
        while (node->child[k])
        {
            ft_syntax_tree_execute(node->child[k], p_environ, p_table_bins, fds);
			if ((node->child[k])->args == NULL)
				return ;
			if (*((int *)ft_vars_get_value(KEY_MUST_EXIT)) == 1)
				return ;
            k++;
        }
    }
}