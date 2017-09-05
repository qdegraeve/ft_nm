/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 10:17:24 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/22 15:43:06 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_lenword(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static int		ft_countword(const char *s, char c)
{
	int	nb;
	int	i;
	int	check;

	i = 0;
	check = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] == c && check)
			check = 0;
		else if (s[i] != c && !check)
		{
			nb++;
			check++;
		}
		i++;
	}
	return (nb);
}

static char		**ft_taballoc(int nbword)
{
	char	**new;

	if (!(new = (char**)malloc((nbword + 1) * sizeof(*new))))
		return (NULL);
	new[0] = NULL;
	return (new);
}

static void		ft_split(char **new, const char *s, char c)
{
	int		i;
	char	*word;
	int		lenword;

	i = 0;
	while (*s != '\0')
	{
		lenword = ft_lenword(s, c);
		if (lenword != 0)
		{
			word = ft_strsub(s, 0, lenword);
			new[i] = word;
			i++;
		}
		s += lenword;
		while (*s == c)
			s++;
	}
	new[i] = NULL;
}

char			**ft_strsplit(char const *s, char c)
{
	char	**new;
	int		nbword;

	if (s == NULL)
		return (ft_taballoc(0));
	nbword = ft_countword(s, c);
	if (!(new = ft_taballoc(nbword)))
		return (NULL);
	ft_split(new, s, c);
	return (new);
}
