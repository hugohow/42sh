/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_tree_execute.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:24:52 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/04 03:30:33 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    ft_syntax_tree_execute(t_node *node, t_env ***p_environ, int fds[], int *p_success)
{
	int k;

	if (node == NULL)
		return ;
    if (node && node->type & TYPE_CMD)
    {
		*p_success = ft_exe_bin(node, p_environ, fds);
		*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)) = *p_success;
    }
	k = 0;
    if (node && node->child && node->child[k])
    {
        while (node->child[k])
        {
            ft_syntax_tree_execute(node->child[k], p_environ, fds, p_success);
			if ((node->child[k])->args == NULL)
				return ;
			if (*((int *)ft_vars_get_value(KEY_MUST_EXIT)) == 1)
				return ;
            k++;
        }
    }
}