/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 10:01:04 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/16 10:01:05 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char	*ptr1;
	char	*ptr2;
	size_t	i;

	if (dest == NULL || src == NULL)
		return (NULL);
	ptr1 = (char*)dest;
	ptr2 = (char*)src;
	i = 0;
	while (i < n)
	{
		if (ptr2[i] == (char)c)
		{
			ptr1[i] = ptr2[i];
			return (&(ptr1[i + 1]));
		}
		ptr1[i] = ptr2[i];
		i++;
	}
	return (NULL);
}
