/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_get_abs_path_cdpath.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 21:58:52 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 18:52:22 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*ft_traverse_cdlists(char **list, char *element, int fds[])
{
	int		i;
	char	*dest_path;

	i = 0;
	while (list && list[i])
	{
		if (ft_strlen(list[i]) == 0)
		{
			i++;
			continue ;
		}
		dest_path = ft_strjoin_(list[i], "/", element);
		if (ft_cd_can_go_to(dest_path) == 1)
		{
			dest_path = ft_path_trim_free(dest_path);
			ft_dprintf(fds[1], "%s\n", dest_path);
			ft_list_free(&list);
			return (dest_path);
		}
		ft_memdel((void **)&dest_path);
		i++;
	}
	ft_list_free(&list);
	return (dest_path);
}

char		*ft_cd_get_abs_path_cdpath(t_env ***p_env, char *element, \
	int fds[], char *cd_path)
{
	char	**list;
	char	*dest_path;

	(void)p_env;
	list = ft_str_separate(cd_path, ':');
	if (ft_strlen(list[0]) == 0)
	{
		dest_path = ft_strjoin("./", element);
		if (ft_cd_can_go_to(dest_path) == 1)
		{
			ft_list_free(&list);
			return (dest_path);
		}
		ft_memdel((void **)&dest_path);
	}
	dest_path = ft_traverse_cdlists(list, element, fds);
	return (dest_path);
}
