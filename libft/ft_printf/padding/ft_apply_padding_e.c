/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_padding_e.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhow-cho <hhow-cho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:57:47 by hhow-cho          #+#    #+#             */
/*   Updated: 2019/06/19 23:16:30 by hhow-cho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char			*ft_add_sign(char *str, t_flag *flag, int sign)
{
	if (ft_can_apply_plus(flag, sign))
		str = ft_str_join("+", str, flag);
	if (ft_can_apply_minus(flag, sign))
		str = ft_str_join("-", str, flag);
	if (ft_can_apply_space(flag, sign))
		str = ft_str_join(" ", str, flag);
	return (str);
}

static size_t		get_size_to_add(t_flag *flag, int sign)
{
	unsigned int	str_len;

	str_len = 0;
	if (ft_can_apply_plus(flag, sign))
		str_len++;
	if (ft_can_apply_minus(flag, sign))
		str_len++;
	if (ft_can_apply_space(flag, sign))
		str_len++;
	return (str_len);
}

static char			*str_to_fill(char *str, t_flag *flag, int sign, char *expo)
{
	char			*to_add;
	unsigned int	to_add_len;
	unsigned int	i;

	to_add_len = get_size_to_add(flag, sign) + ft_strlen(expo);
	if (to_add_len + ft_strlen(str) >= flag->width)
		return (ft_strdup(""));
	if (!(to_add = (char *)ft_memalloc(sizeof(char) * (flag->width + 2))))
		return (NULL);
	i = 0;
	while (to_add_len + ft_strlen(str) + i < flag->width)
	{
		if (flag->key & KEY_FL)
			to_add[i] = ft_can_fill_with_zeros_float(flag, sign) ? '0' : ' ';
		else
			to_add[i] = ft_can_fill_with_zeros(flag, sign) ? '0' : ' ';
		i++;
	}
	to_add[i] = '\0';
	return (to_add);
}

static char			*fill_space(char *str, t_flag *f, char *expo, char *to_a)
{
	if (f->minus == 1)
	{
		str = ft_str_join_r(str, expo, f);
		str = ft_str_join_r(str, to_a, f);
	}
	else
	{
		str = ft_str_join(to_a, str, f);
		str = ft_str_join_r(str, expo, f);
	}
	return (str);
}

char				*ft_apply_padding_e(char *str, t_flag *f, int sign, int e)
{
	char			*to_add;
	char			*expo;

	expo = ft_itoa_e(e);
	if (str[0] && str[0] == '0' && f->conv == 'o')
		f->hash = 0;
	to_add = str_to_fill(str, f, sign, expo);
	if (ft_can_fill_with_zeros(f, sign) || \
		(f->key & KEY_FL && ft_can_fill_with_zeros_float(f, sign)))
	{
		str = ft_str_join(to_add, str, f);
		str = ft_add_sign(str, f, sign);
		str = ft_str_join_r(str, expo, f);
	}
	else
	{
		str = ft_add_sign(str, f, sign);
		str = fill_space(str, f, expo, to_add);
	}
	ft_memdel((void **)&to_add);
	ft_memdel((void **)&expo);
	return (str);
}
