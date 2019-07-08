/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_trim_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 21:24:34 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/07/08 21:25:44 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_path_trim_free(char *abs_path)
{
	char	*new_path;

	new_path = ft_path_trim(abs_path);
	ft_memdel((void **)&abs_path);
	return (new_path);
}
