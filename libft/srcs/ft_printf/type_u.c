/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 17:13:22 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/18 10:52:05 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*type_u_std(unsigned long long d, t_arg *a)
{
	char	*s;

	s = a->p == 0 && d == 0 ? ft_strnew(0) : ft_utoa_base(d, 10);
	a->ret = ft_strlen(s);
	while (a->ret < a->p)
	{
		s = ft_cjoin(ft_strdup("0"), s);
		a->ret++;
	}
	while (a->ret < a->l)
	{
		s = a->f_m ? ft_cjoin(s, ft_strdup(" ")) : ft_cjoin(ft_strdup(" "), s);
		a->ret++;
	}
	return (s);
}

char	*type_u_zero(unsigned long long d, t_arg *a)
{
	char	*s;

	s = a->p == 0 && d == 0 ? ft_strnew(0) : ft_utoa_base(d, 10);
	a->ret = ft_strlen(s);
	if (a->p != 1)
		while (a->ret < a->p && a->ret < a->l)
		{
			s = ft_cjoin(ft_strdup("0"), s);
			a->ret++;
		}
	else
		while (a->ret++ < a->l)
			s = ft_cjoin(ft_strdup("0"), s);
	while (a->ret < a->l)
	{
		s = a->f_m ? ft_cjoin(s, ft_strdup(" ")) : ft_cjoin(ft_strdup(" "), s);
		a->ret++;
	}
	return (s);
}

void	type_u(char type, t_arg *a)
{
	unsigned long long	d;
	char				*s;

	d = va_arg(a->ap, unsigned long long);
	if (a->m_l || type == 'U')
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
	s = a->f_zero && !a->f_m ? type_u_zero(d, a) : type_u_std(d, a);
	a->ret = ft_strlen(s);
	ft_putstr(s);
	ft_strdel(&s);
}
