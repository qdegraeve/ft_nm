/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 11:03:40 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/22 10:34:06 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_s(t_arg *a)
{
	char	*s;
	int		i;
	int		j;

	j = -1;
	if (!(s = ft_strdup(va_arg(a->ap, char *))))
		s = ft_strdup("(null)");
	if (!s[0])
		ft_repeat_char(' ', a->l);
	a->ret = !s[0] || a->p == 0 ? a->l : (int)ft_strlen(s);
	i = a->p >= 0 && a->p < a->ret ? a->l - a->p : a->l - a->ret;
	if (!a->f_m && s[0])
		a->f_zero ? ft_repeat_char('0', i) : ft_repeat_char(' ', i);
	while (s[++j] && a->p > 0 && s[0] && j < a->p)
	{
		a->p < a->ret ? a->ret = a->p : 0;
		ft_putchar(s[j]);
	}
	a->p == -1 ? ft_putstr(s) : 0;
	if (a->f_m && s[0])
		ft_repeat_char(' ', i);
	if (i > 0 && s[0] && a->p != 0)
		a->ret += i;
	ft_strdel(&s);
}

void	count_ret(char **to_print, t_arg *a)
{
	int				i;

	i = -1;
	while (to_print[++i])
		a->ret++;
}

void	type_ls(wchar_t *ws, t_arg *a)
{
	unsigned int	w;
	int				i;
	char			**p;
	char			*s;
	char			*t;

	i = -1;
	t = !ws ? ft_strdup("(null)") : ft_strnew(0);
	while (ws && ws[++i] && (a->p != -1 ? a->ret < a->p : 1))
	{
		w = (unsigned int)ws[i];
		s = ft_utoa_base(w, 2);
		count_ret((p = unicode_masks(s)), a);
		if (a->p == -1 || (a->p != -1 && a->ret <= a->p))
			t = ft_cjoin((char*)t, (char*)stock_wchar(p));
	}
	a->ret = ft_strlen(t);
	a->f_m ? write(1, t, a->ret) : 0;
	if ((i = a->l - a->ret))
		a->f_zero && !a->f_m ? ft_repeat_char('0', i) : ft_repeat_char(' ', i);
	!a->f_m ? write(1, t, a->ret) : 0;
	ft_strdel(&t);
	a->ret = a->l > a->ret ? a->l : a->ret;
}

void	type_s_ls(char type, t_arg *a)
{
	wchar_t			*ws;

	if (type == 'S' || a->m_l)
	{
		ws = va_arg(a->ap, wchar_t*);
		type_ls(ws, a);
	}
	else
		type_s(a);
}
