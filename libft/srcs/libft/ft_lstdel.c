/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 09:59:51 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/16 09:59:52 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*backup;

	if (*alst == NULL || del == NULL)
		return ;
	tmp = *alst;
	while (tmp)
	{
		backup = tmp->next;
		ft_lstdelone(&tmp, (*del));
		tmp = backup;
	}
	*alst = NULL;
}
