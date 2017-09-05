/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 10:56:16 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/30 16:48:11 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "get_next_line.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <inttypes.h>

typedef struct		s_arg
{
	va_list		ap;
	int			ret;
	int			i;
	int			f_p;
	int			f_m;
	int			f_sp;
	int			f_h;
	int			f_none;
	int			f_zero;
	int			l;
	int			p;
	int			m_h;
	int			m_hh;
	int			m_l;
	int			m_ll;
	int			m_z;
	int			m_j;
}					t_arg;

/*
**		tools
*/

void				ft_putnbru(unsigned int nb);
char				*ft_utoa_base(unsigned long long value, int base);
char				*ft_ltoa_base(long long value, int base);
char				*ft_dtoa_base(double value, int base, int precision,
		t_arg *a);
void				ft_repeat_char(char c, int nbr);
char				*str_lower(char *str);
void				count_ret(char **to_print, t_arg *a);

/*
**		type conversion
*/

void				type_d(char type, t_arg *a);
void				type_x(char type, t_arg *a);
void				type_u(char type, t_arg *a);
void				type_o(char type, t_arg *a);
void				type_s_ls(char type, t_arg *a);
void				type_c_lc(char type, t_arg *a);
void				type_percent(t_arg *a);
void				type_f(t_arg *a);
void				type_p(t_arg *a);

/*
**		flags
*/

void				check_flags(char *format, t_arg *a);
void				check_min_lenght(char *format, t_arg *a);
void				check_precision(char *format, t_arg *a);
void				set_default_precision(char type, t_arg *a);
void				check_modifier(char *format, t_arg *a);

/*
**		unicode
*/

char				**unicode_masks(char *wc);
void				masks_fill(char *mask, char *wc);
void				print_wchar(char **to_print);
unsigned char		*stock_wchar(char **to_print);

int					ft_printf(char *format, ...);
void				check_type(char *format, t_arg *a);

# define DEBUG ft_printf("- %s - l%d - %s\n", __FILE__, __LINE__, __FUNCTION__);

#endif
