/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:12:01 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/28 21:55:57 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 30
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "libft.h"

int					get_next_line(const int fd, char **line);
void				ft_lstdelnode(t_list **head, size_t pos);
#endif
