/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 11:03:31 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/25 17:30:48 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*str_lower(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

void	ft_repeat_char(char c, int nbr)
{
	int i;

	i = 0;
	while (i < nbr)
	{
		write(1, &c, 1);
		i++;
	}
}

char	*type_x_std(unsigned long long d, t_arg *a)
{
	char	*s;

	s = a->p == 0 && d == 0 ? ft_strnew(0) : ft_utoa_base(d, 16);
	a->ret = ft_strlen(s);
	while (a->ret < a->p)
	{
		s = ft_cjoin(ft_strdup("0"), s);
		a->ret++;
	}
	a->f_h && d ? s = ft_cjoin(ft_strdup("0X"), s) : 0;
	a->ret += a->f_h ? 2 : 0;
	while (a->ret < a->l)
	{
		s = a->f_m ? ft_cjoin(s, ft_strdup(" ")) : ft_cjoin(ft_strdup(" "), s);
		a->ret++;
	}
	return (s);
}

char	*type_x_zero(unsigned long long d, t_arg *a)
{
	char	*s;

	s = a->p == 0 && d == 0 ? ft_strnew(0) : ft_utoa_base(d, 16);
	a->ret = ft_strlen(s);
	if (a->p != 1)
	{
		while (a->ret++ < a->p)
			s = ft_cjoin(ft_strdup("0"), s);
		a->ret += a->f_h ? 2 : 0;
	}
	else
	{
		a->ret += a->f_h ? 2 : 0;
		while (a->ret++ < a->l)
			s = ft_cjoin(ft_strdup("0"), s);
	}
	a->f_h && d ? s = ft_cjoin(ft_strdup("0X"), s) : 0;
	while (a->ret <= a->l)
	{
		s = a->f_m ? ft_cjoin(s, ft_strdup(" ")) : ft_cjoin(ft_strdup(" "), s);
		a->ret++;
	}
	return (s);
}

void	type_x(char type, t_arg *a)
{
	unsigned long long	d;
	char				*s;

	d = va_arg(a->ap, unsigned long long);
	if (a->m_l)
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
	s = a->f_zero && !a->f_m ? type_x_zero(d, a) : type_x_std(d, a);
	a->ret = ft_strlen(s);
	if (type == 'x')
		s = str_lower(s);
	ft_putstr(s);
	ft_strdel(&s);
}
