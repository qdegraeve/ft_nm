/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 16:37:34 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/19 20:19:22 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_c(t_arg *a)
{
	char	c;

	c = va_arg(a->ap, int);
	a->ret++;
	a->f_m ? ft_putchar(c) : 0;
	while (a->ret < a->l)
	{
		a->f_zero ? ft_putchar('0') : ft_putchar(' ');
		a->ret++;
	}
	!a->f_m ? ft_putchar(c) : 0;
}

void	type_c_lc(char type, t_arg *a)
{
	unsigned int	i;
	char			*s;
	char			**p;

	if (type == 'C' || a->m_l)
	{
		i = va_arg(a->ap, unsigned int);
		s = ft_utoa_base(i, 2);
		count_ret((p = unicode_masks(s)), a);
		a->l > a->ret && !a->f_m ? ft_repeat_char(' ', a->l - a->ret) : 0;
		print_wchar(p);
		a->l > a->ret && a->f_m ? ft_repeat_char(' ', a->l - a->ret) : 0;
		a->ret = a->l > a->ret ? a->l : a->ret;
	}
	else
		type_c(a);
}
