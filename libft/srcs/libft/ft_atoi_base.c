/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 20:39:51 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/22 14:14:37 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(const char *str, int base)
{
	int		sign;
	size_t	res;
	int		i;

	i = 0;
	res = 0;
	sign = 1;
	while ((unsigned char)str[i] < 33)
		i++;
	if (str[i] == '-' && ft_isdigit(str[i + 1]) == 1)
	{
		sign = -sign;
		i++;
	}
	if (str[i] == '+' && ft_isdigit(str[i + 1]) == 1)
		i++;
	while (ft_isdigit(str[i]) == 1)
	{
		res = (res * 10) + str[i] - '0';
		i++;
	}
	return (res * sign);
}
