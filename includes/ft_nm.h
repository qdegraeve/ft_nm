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

typedef struct s_flags
{
	char				p;
	char				a;
	char				n;
	char				r;
	char				u;
	char				U;
	char				text_sect;
	char				data_sect;
	char				bss_sect;
	int					nb_files;
	int					nb_sects;
	char				**files;
	struct section		**sects;
	struct section_64	**sects64;
}				t_flags;

typedef struct	s_symbol
{
	char			type;
	char			*name;
	struct nlist_64	symbol;
	struct s_symbol	*next;
}				t_symbol;

#endif