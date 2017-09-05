/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 12:13:01 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/22 12:43:09 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_min_lenght(char *format, t_arg *a)
{
	while ((format[a->i] > '0' && format[a->i] <= '9') || format[a->i] == '*')
	{
		if (format[a->i] > '0' && format[a->i] <= '9')
			a->l = ft_atoi(format + a->i);
		while ((format[a->i] >= '0' && format[a->i] <= '9'))
		{
			if (format[a->i + 1] != '\0')
				a->i++;
			else
				return ;
		}
		if (format[a->i] == '*')
		{
			a->l = va_arg(a->ap, int);
			a->l < 0 ? a->f_m = 1 : 0;
			a->l < 0 ? a->l = -1 * a->l : 0;
			if (format[a->i + 1] != '\0')
				a->i++;
		}
	}
	if (format[a->i] == '.')
		check_precision(format, a);
	else
		check_modifier(format, a);
}

void	check_precision(char *format, t_arg *a)
{
	a->i++;
	if (format[a->i] >= '0' && format[a->i] <= '9')
		a->p = ft_atoi(format + a->i);
	else if (format[a->i] == '*')
	{
		a->p = va_arg(a->ap, int);
		a->p < 0 ? a->p = -1 : 0;
	}
	else
		a->p = 0;
	while ((format[a->i] >= '0' && format[a->i] <= '9') || format[a->i] == '*')
	{
		if (format[a->i + 1] != '\0')
			a->i++;
		else
			return ;
	}
	check_modifier(format, a);
}

void	set_default_precision(char type, t_arg *a)
{
	if (a->p == -1 && type != 'd' && type != 'i')
	{
		a->p = type == 'c' || type == 's' || type == 'S' ? -1 : 1;
		if (type == 'f' || type == 'F' || type == 'e' || type == 'E' || type
				== 'g' || type == 'G')
			a->p = 6;
	}
}
