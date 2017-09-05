/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 10:01:42 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/16 10:01:44 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*ptr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	ptr = (char*)s;
	while (i < n)
	{
		if (ptr[i] == (char)c)
			return (&(ptr[i]));
		i++;
	}
	return (NULL);
}
