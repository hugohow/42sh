/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_tree_execute.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:45:16 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/25 23:19:38 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_syntax_tree_execute(t_node *node, t_env ***p_env, int fds[])
{
	int k;

	if (node == NULL)
		return (0);
	if (node && node->type & TYPE_CMD)
		return (ft_syntax_tree_execute_node(node, p_env, fds));
	k = 0;
	if (node && node->type & TYPE_SEMI_COLON && node->child && node->child[k])
	{
		while (node->child[k])
		{
			if ((ft_syntax_tree_execute(node->child[k], p_env, fds)) < 0)
				return (1);
			if (*((int *)ft_vars_get_value(KEY_MUST_EXIT)) == 1)
				return (0);
			k++;
		}
	}
	else if (node && node->type & TYPE_PIPE && node->child && node->child[k])
	{
		int *ls_pfd;

		ls_pfd = ft_memalloc(((node->nb_child) * 2 + 2) * sizeof(int));
		int j;

		j = 0;
		while (j < (node->nb_child + 1) * 2)
		{
			// ls_pfd[j] = j + 3;
			// j++;
			int pfd[2];
			pipe(pfd);   
			ls_pfd[j] = pfd[0];
			j++;
			ls_pfd[j] = pfd[1];
			j++;
		}
		ls_pfd[j] = 0;
		while (node->child[k])
		{
			int fds_pipe[3];

			if (k == 0)
			{
				fds_pipe[0] = fds[0];
				fds_pipe[1] = ls_pfd[1];
				fds_pipe[2] = ls_pfd[1];
			}
			else if (node->child[k + 1])
			{
				fds_pipe[0] = ls_pfd[(k-1) * 2];
				fds_pipe[1] = ls_pfd[(k) * 2 + 1];
				fds_pipe[2] = ls_pfd[(k) * 2 + 1];
			}
			else
			{
				fds_pipe[0] = ls_pfd[(k-1) * 2];
				fds_pipe[1] = fds[1];
				fds_pipe[2] = fds[2];
			}
			// ft_printf("k :%d, cmd : %s, %d %d %d\n", k, (node->child[k])->cmd, fds_pipe[0], fds_pipe[1], fds_pipe[2]);
			if ((ft_syntax_tree_execute(node->child[k], p_env, fds_pipe)) < 0)
			{
				if (fds_pipe[0] != 0)
					close(fds_pipe[0]);
				if (fds_pipe[1] != 1)
					close(fds_pipe[1]);
				return (1);
			}
			if (fds_pipe[0] != 0)
				close(fds_pipe[0]);
			if (fds_pipe[1] != 1)
				close(fds_pipe[1]);
			if (*((int *)ft_vars_get_value(KEY_MUST_EXIT)) == 1)
				return (0);
			k++;
		}
	}
	return (0);
}
