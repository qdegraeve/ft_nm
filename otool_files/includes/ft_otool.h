#ifndef FT_OTOOL_H
# define FT_OTOOL_H

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
# define MUNMAP_ERROR	5

union					u_cmp
{
	char				*str;
	unsigned long		value;
};

typedef struct			s_cpu_type_names {
	cpu_type_t			cputype;
	const char			*cpu_name;
}						t_cpu_type_names;

typedef struct			s_flags
{
	char				exit_code;
	char				should_swap;
	char				is_fat;
	char				is_lib;
	char				t;
	char				d;
	char				is_32;
	off_t				file_size;
	int					nb_files;
	unsigned int		nfat_arch;
	cpu_type_t			cputype;
	char				**files;
}						t_flags;

/*
** NM handlers
*/
int						otool(void *ptr, t_flags flags);
int						handle_32(void *ptr, t_flags flags);
int						handle_64(void *ptr, t_flags flags);
int						handle_lib(void *ptr, t_flags flags);
int						handle_fat(void *ptr, t_flags flags);
char					get_type(uint8_t n_type, uint8_t n_sect, t_flags flags);

/*
** Errors functions
*/
int						file_corrupted(t_flags *flags);
void					unknown_flag(char flag);

/*
** Shared functions
*/
void					reset_flags(t_flags *flags, char fat);
cpu_type_t				cpu_type(char *cpu_type_name);

/*
** TODO: Swap functions
*/
uint16_t				swap_16(uint16_t to_swap);
uint32_t				swap_32(uint32_t to_swap);
uint64_t				swap_64(uint64_t to_swap);
struct symtab_command	swap_symtab_command(struct symtab_command *sc,
							t_flags flags);

#endif
