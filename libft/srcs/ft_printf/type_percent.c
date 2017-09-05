/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_percent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 15:19:44 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/22 10:30:18 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_percent(t_arg *a)
{
	a->ret = 1;
	a->f_m == 1 ? ft_putchar('%') : 0;
	while (a->ret < a->l)
	{
		a->f_zero && !a->f_m ? ft_putchar('0') : ft_putchar(' ');
		a->ret++;
	}
	a->f_m == 0 ? ft_putchar('%') : 0;
}
