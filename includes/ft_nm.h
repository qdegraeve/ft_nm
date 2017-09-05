#ifndef	FT_NM_H
# define FT_NM_H

# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "../libft/include/ft_printf.h"

union	u_cmp
{
	char			*str;
	unsigned long	value;
};

typedef struct	s_symbol
{
	char			type;
	char			*name;
	struct nlist_64	symbol;
	struct s_symbol	*next;
}				t_symbol;

#endif