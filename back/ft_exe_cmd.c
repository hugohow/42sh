/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:41:29 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/18 13:07:12 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    execute_tree(t_node *node, t_ht *table_bins, t_env ***p_environ, int fds[], int *p_success)
{
	if (node == NULL)
		return ;
    if (node->type & TYPE_CMD)
    {
        if (is_exit(node->cmd) == 1)
            ft_exit(node->cmd, *p_success, fds);
        else
		{
			*p_success = ft_exe_bin(node, table_bins, p_environ, fds);
			ft_env_change_line("?", ft_strjoin("?=", ft_itoa(*p_success)), *p_environ);
		}
    }
    if (node->child)
    {
        int k;

        k = 0;
        while (node->child[k])
        {
            t_node *node_child;

            node_child = node->child[k];
            execute_tree(node_child, table_bins, p_environ, fds, p_success);
            k++;
        }
    }
}