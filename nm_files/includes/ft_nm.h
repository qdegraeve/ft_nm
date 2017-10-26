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
# include "../../libft/include/ft_printf.h"
# include <ar.h>

# define MALLOC_ERROR	1
# define FILE_CORRUPTED 2
# define FSTAT_ERROR	3
# define OPEN_ERROR		4
# define MMAP_ERROR		5
# define NO_SYMTAB		6
# define FILE_NOT_VALID 7
# define MUNMAP_ERROR		5

union			u_cmp
{
	char				*str;
	unsigned long		value;
};

typedef struct	s_cpu_type_names {
	cpu_type_t			cputype;
	const char			*cpu_name;
}				t_cpu_type_names;

typedef struct	s_symbol
{
	char				type;
	uint8_t				n_type;
	uint8_t				n_sect;
	uint64_t			value;
	char				*name;
	struct s_symbol		*next;
}				t_symbol;

typedef struct	s_flags
{
	char				exit_code;
	char				should_swap;
	char				is_fat;
	char				is_lib;
	char				p;
	char				a;
	char				n;
	char				r;
	char				u;
	char				u_up;
	char				is_32;
	off_t				file_size;
	char				text_sect;
	char				data_sect;
	char				bss_sect;
	int					nb_files;
	int					nb_sects;
	unsigned int		nfat_arch;
	cpu_type_t			cputype;
	char				**files;
	t_symbol			*symbols;
}				t_flags;

/*
** NM handlers
*/
int						nm(void *ptr, t_flags flags);
int						handle_32(void *ptr, t_flags flags);
int						handle_64(void *ptr, t_flags flags);
int						handle_lib(void *ptr, t_flags flags);
int						handle_fat(void *ptr, t_flags flags);
char					get_type(uint8_t n_type, uint8_t n_sect, t_flags flags);
void					insert_at(t_symbol **list, t_symbol *new,
							t_flags flags);
void					print_output(t_symbol *symbols, t_flags flags);

/*
** Shared functions
*/
void					reset_flags(t_flags *flags, char fat);
cpu_type_t				cpu_type(char *cpu_type_name);
int						file_corrupted(t_flags *flags);

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
