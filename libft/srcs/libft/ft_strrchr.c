/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 10:16:34 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/16 10:17:13 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (c < 0 || c > 255 || c == '\0')
		return (char*)(s + i);
	while (s[i] != (char)c && i >= 0)
		i--;
	if (i < 0)
		return (NULL);
	return (char*)(s + i);
}
