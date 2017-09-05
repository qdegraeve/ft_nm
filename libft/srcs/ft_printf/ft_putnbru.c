/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 21:31:45 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/11 21:32:39 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbru(unsigned int nb)
{
	if (nb < 10)
	{
		ft_putchar(nb + 48);
		return ;
	}
	ft_putnbru(nb / 10);
	ft_putchar((nb % 10) + 48);
	return ;
}
