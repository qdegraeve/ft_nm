/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 12:14:44 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/16 10:46:22 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	invalid_conv(char to_print, t_arg *a)
{
	a->ret = a->l ? a->l : 1;
	if (!a->f_m)
		a->f_zero ? ft_repeat_char('0', a->l - 1)
			: ft_repeat_char(' ', a->l - 1);
	ft_putchar(to_print);
	if (a->f_m)
		a->f_zero ? ft_repeat_char('0', a->l - 1)
			: ft_repeat_char(' ', a->l - 1);
}

void	check_type(char *format, t_arg *a)
{
	set_default_precision(format[a->i], a);
	if (format[a->i] == 's' || format[a->i] == 'S')
		type_s_ls(format[a->i], a);
	else if (format[a->i] == 'd' || format[a->i] == 'i' || format[a->i] == 'D')
		type_d(format[a->i], a);
	else if (format[a->i] == '%')
		type_percent(a);
	else if (format[a->i] == 'x' || format[a->i] == 'X')
		type_x(format[a->i], a);
	else if (format[a->i] == 'o' || format[a->i] == 'O')
		type_o(format[a->i], a);
	else if (format[a->i] == 'u' || format[a->i] == 'U')
		type_u(format[a->i], a);
	else if (format[a->i] == 'f' || format[a->i] == 'F')
		type_f(a);
	else if (format[a->i] == 'c' || format[a->i] == 'C')
		type_c_lc(format[a->i], a);
	else if (format[a->i] == 'p')
		type_p(a);
	else
		invalid_conv(format[a->i], a);
}
