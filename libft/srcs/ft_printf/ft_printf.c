/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 12:36:34 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/22 13:13:59 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_modifier(char *f, t_arg *a)
{
	while (f[a->i] == 'h' || f[a->i] == 'l' || f[a->i] == 'j' || f[a->i] == 'z')
	{
		if (f[a->i] == 'h' && f[a->i + 1] == 'h')
			a->m_hh = 1;
		else if (f[a->i] == 'h')
			a->m_h = 1;
		else if (f[a->i] == 'l' && f[a->i + 1] == 'l')
			a->m_ll = 1;
		else if (f[a->i] == 'l')
			a->m_l = 1;
		else if (f[a->i] == 'j')
			a->m_j = 1;
		else if (f[a->i] == 'z')
			a->m_z = 1;
		if (((a->m_ll || a->m_hh) && f[a->i + 2]) || f[a->i + 1])
			a->i = a->m_ll || a->m_hh ? a->i + 2 : a->i + 1;
		else
			return ;
	}
	check_type(f, a);
}

void	init_struct(t_arg *a)
{
	a->ret = 0;
	a->f_p = 0;
	a->f_m = 0;
	a->f_sp = 0;
	a->f_h = 0;
	a->f_none = 0;
	a->f_zero = 0;
	a->l = 0;
	a->m_hh = 0;
	a->m_h = 0;
	a->m_l = 0;
	a->m_ll = 0;
	a->m_j = 0;
	a->m_z = 0;
	a->p = -1;
}

int		ft_printf(char *format, ...)
{
	t_arg		a;
	int			ret;

	ret = 0;
	a.i = 0;
	va_start(a.ap, format);
	while (format[a.i])
	{
		init_struct(&a);
		if (format[a.i] == '%')
		{
			if (format[++a.i] == '\0')
				break ;
			check_flags(format, &a);
		}
		else
		{
			ft_putchar(format[a.i]);
			ret++;
		}
		ret += a.ret;
		a.i++;
	}
	va_end(a.ap);
	return (ret);
}
