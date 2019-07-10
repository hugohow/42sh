/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_get_dest_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 19:05:08 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/10 12:41:26 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	handle_error(char *dest_path, char *to_free, \
	t_env ***p_env, int fds[])
{
	ft_putstr_fd(\
	"minishell cd: error retrieving current directory: getcwd:"\
	, fds[2]);
	ft_putstr_fd(\
	" cannot access parent directories: No such file or directory.\n"\
	, fds[2]);
	ft_cd_change_env(to_free, p_env);
	ft_memdel((void **)&dest_path);
}

static char	*ft_solve_dot_dot(char *dest_path, t_env ***p_env,\
	long long flag, int fds[])
{
	char *to_free;

	if (~(flag & FLAG_CD_P))
	{
		if (ft_strncmp("/", dest_path, 1) != 0)
		{
			to_free = dest_path;
			dest_path = ft_cd_get_pwd_plus_element(p_env, to_free);
			ft_memdel((void **)&to_free);
		}
		to_free = dest_path;
		dest_path = ft_path_trim(to_free);
		if (ft_cd_can_go_to(dest_path) == -1)
		{
			handle_error(dest_path, to_free, p_env, fds);
			return (NULL);
		}
		ft_memdel((void **)&to_free);
	}
	dest_path = ft_path_trim_free(dest_path);
	return (dest_path);
}

/*
** 1, 2 ) If no directory operand is given and the HOME..
** 3 ) If the directory operand begins with a <slash> character
** 4 ) If the first component of the directory operand is dot or dot-dot
*/

static char	*get_dest_path(char *element, t_env ***p_env, \
	long long flag, int fds[])
{
	char *dest_path;

	dest_path = NULL;
	if (!element)
		return (ft_cd_get_path_home(p_env, fds));
	else if (ft_strncmp("/", element, 1) == 0)
		return (ft_cd_get_absolute_path(element, fds));
	if (ft_strncmp(element, ".", 1) == 0 || ft_strncmp(element, "..", 2) == 0)
		dest_path = ft_strdup(element);
	else if (ft_strcmp(element, "-") == 0)
		return (ft_cd_get_old_path(p_env, fds));
	else
		dest_path = ft_cd_get_path_cdpath(element, p_env, fds);
	if (ft_cd_can_go_to_message(dest_path, element, fds) == -1)
	{
		ft_memdel((void **)&dest_path);
		return (NULL);
	}
	dest_path = ft_solve_dot_dot(dest_path, p_env, flag, fds);
	return (dest_path);
}

char		*ft_cd_get_dest_path(char *element, t_env ***p_env, \
	long long flag, int fds[])
{
	char *dest_path;

	if (!(dest_path = get_dest_path(element, p_env, flag, fds)))
		return (NULL);
	if (ft_strlen(dest_path) > PATH_MAX)
	{
		ft_memdel((void **)&dest_path);
		ft_putstr_fd("minishell: cd: path too long\n", fds[2]);
		return (NULL);
	}
	return (dest_path);
}
