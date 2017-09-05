/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 10:07:16 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/16 10:07:22 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*str;

	if (src == NULL)
		return (NULL);
	if (!(str = ft_strnew(ft_strlen(src))))
		return (NULL);
	ft_strcpy(str, src);
	return (str);
}
