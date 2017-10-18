#ifndef FT_NM_H
# define FT_NM_H

# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "../libft/include/ft_printf.h"

union			u_cmp
{
	char				*str;
	unsigned long		value;
};

typedef struct	s_cpu_type_names {
	cpu_type_t			cputype;
	const char			*cpu_name;
}				t_cpu_type_names;

typedef struct	s_flags
{
	char				should_swap;
	char				p;
	char				a;
	char				n;
	char				r;
	char				u;
	char				u_up;
	char				is_32;
	char				text_sect;
	char				data_sect;
	char				bss_sect;
	int					nb_files;
	int					file_offset;
	int					nb_sects;
	char				*arch;
	char				**files;
	struct section		**sects;
	struct section_64	**sects64;
}				t_flags;

typedef struct	s_symbol
{
	char				type;
	uint8_t				n_type;
	uint8_t				n_sect;
	uint64_t			value;
	char				*name;
	struct s_symbol		*next;
}				t_symbol;

/*
** NM handlers
*/
void					nm(void *ptr, t_flags flags);
void					handle_32(void *ptr, t_flags flags);
void					handle_64(void *ptr, t_flags flags);
void					organizer32(int nsyms, int symoff,
							int stroff, void *ptr, t_flags flags);
void					organizer64(int nsyms, int symoff,
							int stroff, void *ptr, t_flags flags);
char					get_type(uint8_t n_type, uint8_t n_sect, t_flags flags);
t_symbol				*create_elem64(struct nlist_64 symbol,
							char *name, t_flags flags);
t_symbol				*create_elem32(struct nlist symbol,
							char *name, t_flags flags);
void					insert_at(t_symbol **list, t_symbol *new,
							t_flags flags);
void					print_output(t_symbol *symbols, t_flags flags);
void					handle_fat(void *ptr, t_flags flags);

/*
** Shared functions
*/
void					reset_flags(t_flags *flags);

/*
** Comparison function
*/
int						no_comp(t_symbol *sym1, t_symbol *sym2);
int						name_comp(t_symbol *sym1, t_symbol *sym2);
int						value_comp(t_symbol *sym1, t_symbol *sym2);

/*
** TODO: Swap functions
*/
uint16_t				swap_16(uint16_t to_swap);
uint32_t				swap_32(uint32_t to_swap);
uint64_t				swap_64(uint64_t to_swap);
struct symtab_command	swap_symtab_command(struct symtab_command *sc,
							t_flags flags);

#endif
