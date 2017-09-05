/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 12:12:03 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/18 13:41:55 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*type_o_std(unsigned long long d, t_arg *a)
{
	char	*s;

	s = a->p == 0 && d == 0 ? ft_strnew(0) : ft_utoa_base(d, 8);
	a->ret = ft_strlen(s);
	while (a->ret < a->p)
	{
		s = ft_cjoin(ft_strdup("0"), s);
		a->ret++;
	}
	a->ret += a->f_h && s[0] != 0 ? 1 : 0;
	a->f_h && s[0] != '0' ? s = ft_cjoin(ft_strdup("0"), s) : 0;
	while (a->ret < a->l)
	{
		s = a->f_m ? ft_cjoin(s, ft_strdup(" ")) : ft_cjoin(ft_strdup(" "), s);
		a->ret++;
	}
	return (s);
}

char	*type_o_zero(unsigned long long d, t_arg *a)
{
	char	*s;

	s = a->p == 0 && d == 0 ? ft_strnew(0) : ft_utoa_base(d, 8);
	a->ret = ft_strlen(s);
	if (a->p != 1)
		while (a->ret++ < a->p)
			s = ft_cjoin(ft_strdup("0"), s);
	else
		while (a->ret++ < a->l)
			s = ft_cjoin(ft_strdup("0"), s);
	a->ret += a->f_h && s[0] != '0' ? 1 : 0;
	a->f_h && s[0] != '0' ? s = ft_cjoin(ft_strdup("0"), s) : 0;
	while (a->ret <= a->l)
	{
		s = a->f_m ? ft_cjoin(s, ft_strdup(" ")) : ft_cjoin(ft_strdup(" "), s);
		a->ret++;
	}
	return (s);
}

void	type_o(char type, t_arg *a)
{
	unsigned long long	d;
	char				*s;

	d = va_arg(a->ap, unsigned long long);
	if (a->m_l || type == 'O')
		d = (unsigned long)d;
	else if (a->m_h)
		d = (unsigned short int)d;
	else if (a->m_hh)
		d = (unsigned char)d;
	else if (a->m_j)
		d = (uintmax_t)d;
	else if (a->m_z)
		d = (size_t)d;
	else if (!a->m_ll)
		d = (unsigned int)d;
	s = a->f_zero && !a->f_m ? type_o_zero(d, a) : type_o_std(d, a);
	a->ret = ft_strlen(s);
	ft_putstr(s);
	ft_strdel(&s);
}
