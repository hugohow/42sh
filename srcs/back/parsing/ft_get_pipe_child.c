/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pipe_child.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 20:28:36 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/25 20:32:53 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_is_empty(char *str)
{
	char *tmp;

	if (!(tmp = ft_strtrim(str)))
		return (1);
	if (ft_strlen(tmp) == 0)
	{
		ft_memdel((void **)&tmp);
		return (1);
	}
	ft_memdel((void **)&tmp);
	return (0);
}

static char	**has_syntax_error(char **list)
{
	int		k;

	k = 0;
	while (list[k])
	{
		if (ft_is_empty(list[k]) && list[k + 1])
		{
			ft_dprintf(2, \
				"21sh: syntax error near unexpected token '|'\n");
			ft_list_free(&list);
			return (NULL);
		}
		k++;
	}
	return (list);
}

int			ft_get_pipe_child(t_node *node, t_env **copy_env)
{
	char	**list;
	int		k;
	t_node	**child;

	if (ft_strchr(node->cmd, '|') == NULL)
		return (0);
	if (!(list = ft_str_separate(node->cmd, '|')))
		return (1);
	child = NULL;
	if (!(list = has_syntax_error(list)))
	{
		*((int *)ft_vars_get_value(KEY_SUCCESS_EXIT)) = 2;
		return (2);
	}
	if (!(child = (t_node **)ft_memalloc((ft_list_size(list) + 1)\
	* sizeof(t_node *))))
	{
		ft_list_free(&list);
		return (1);
	}
	k = -1;
	while (list[++k] && (child[k] = create_node(TYPE_PIPE, list[k], copy_env)))
		;
	node->nb_child = k;
	node->child = child;
	ft_list_free(&list);
	return (0);
}