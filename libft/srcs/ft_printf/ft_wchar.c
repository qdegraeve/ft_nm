/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 19:14:23 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/19 20:24:23 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			masks_fill(char *mask, char *wc)
{
	int		mlen;
	int		wlen;

	mlen = ft_strlen(mask) - 1;
	wlen = ft_strlen(wc) - 1;
	while (mlen)
	{
		while (mask[mlen] != 'x' && mlen)
		{
			mlen--;
		}
		if (wlen >= 0)
			mask[mlen--] = wc[wlen--];
		wlen == -1 && mask[mlen] == 'x' ? mask[mlen--] = '0' : 0;
	}
}

unsigned char	bin_a_to_u(char *s)
{
	int				i;
	unsigned char	bin;
	unsigned char	ret;

	ret = 0;
	bin = 1;
	i = ft_strlen(s);
	while (--i >= 0)
	{
		ret += (bin * (s[i] - '0'));
		bin *= 2;
	}
	return (ret);
}

unsigned char	*stock_wchar(char **to_print)
{
	unsigned char	*s;
	unsigned char	c;
	int				i;

	i = -1;
	while (to_print[++i])
		;
	s = (unsigned char *)malloc(i);
	i = 0;
	while (to_print[i])
	{
		c = bin_a_to_u(to_print[i]);
		s[i] = c;
		ft_strdel(&to_print[i]);
		i++;
	}
	s[i] = '\0';
	if (to_print)
		free(to_print);
	return (s);
}

void			print_wchar(char **to_print)
{
	unsigned char	c;
	int				i;

	i = 0;
	while (to_print[i])
	{
		c = bin_a_to_u(to_print[i]);
		write(1, &c, 1);
		ft_strdel(&to_print[i]);
		i++;
	}
	if (to_print)
		free(to_print);
}

char			**unicode_masks(char *wc)
{
	char			*m;
	char			**to_print;

	if (ft_strlen(wc) <= 7)
		masks_fill(m = ft_strdup("0xxxxxxx"), wc);
	else if (ft_strlen(wc) <= 11)
		masks_fill(m = ft_strdup("110xxxxx 10xxxxxx"), wc);
	else if (ft_strlen(wc) <= 16)
		masks_fill(m = ft_strdup("1110xxxx 10xxxxxx 10xxxxxx"), wc);
	else
		masks_fill(m = ft_strdup("11110xxx 10xxxxxx 10xxxxxx 10xxxxxx"), wc);
	to_print = ft_strsplit(m, ' ');
	ft_strdel(&m);
	ft_strdel(&wc);
	return (to_print);
}
