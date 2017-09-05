/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 09:50:26 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/22 18:26:45 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_numlen(size_t num, int base)
{
	int len;

	len = 0;
	while ((num = num / base))
		len++;
	return (len);
}

char	*ft_itoa_base(int value, int base)
{
	int		len;
	char	*ret;
	int		sign;

	if (base < 2 || base > 16)
		return (NULL);
	len = (base == 10 && value < 0) ? 2 : 1;
	sign = value < 0 ? -1 : 1;
	len = ft_numlen(value, base);
	if (!(ret = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ret[len--] = '\0';
	while (len >= 0 && value / base != 0)
	{
		ret[len] = value % base < 10 ? value % base * sign + '0' :
			value % base * sign + '7';
		value /= base;
		len--;
	}
	ret[len--] = value % base < 10 ? value % base * sign + '0' :
		value % base * sign + '7';
	if (len == 0)
		ret[0] = '-';
	return (ret);
}
