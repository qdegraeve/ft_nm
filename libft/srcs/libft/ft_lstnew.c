/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 10:00:28 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/16 10:00:33 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	new = NULL;
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	ft_bzero(new, sizeof(t_list));
	new->content_size = 0;
	new->content = NULL;
	if (content == NULL)
		return (new);
	else
	{
		new->content_size = content_size;
		if (!(new->content = malloc(content_size)))
			return (NULL);
		ft_bzero(new->content, content_size);
		ft_memcpy(new->content, content, content_size);
	}
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
