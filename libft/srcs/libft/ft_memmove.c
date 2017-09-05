/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 10:02:27 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/16 10:02:28 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	tmp[n];
	size_t	i;

	i = 0;
	while (i < n)
	{
		tmp[i] = ((char*)src)[i];
		i++;
	}
	i = 0;
	while (i < n && dest)
	{
		((char*)dest)[i] = tmp[i];
		i++;
	}
	((char*)dest)[i] = '\0';
	return (dest);
}
