#include "ft_nm.h"

int		no_comp(t_symbol *sym1, t_symbol *sym2)
{
	sym1 = NULL;
	sym2 = NULL;
	return (1);
}

int		name_comp(t_symbol *sym1, t_symbol *sym2)
{
	return (ft_strcmp(sym1->name, sym2->name));
}

int		value_comp(t_symbol *sym1, t_symbol *sym2)
{
	return (sym1->symbol.n_value - sym2->symbol.n_value);
}

char	get_type(struct nlist_64 array, t_flags flags)
{
		int type;

		type = array.n_type & N_TYPE;
		if (type == N_UNDF)
			type = 'u';
		else if (type == N_PBUD)
			type = 'u';
		else if (type == N_ABS)
			type = 'a';
		else if (type == N_SECT)
		{
			if (array.n_sect == flags.text_sect)
				type = 't';
			else if (array.n_sect == flags.data_sect)
				type = 'd';
			else if (array.n_sect == flags.bss_sect)
				type = 'b';
		}
		else if (type == N_INDR)
			type = 'i';
		else
			type = '?';
		if ((array.n_type & N_EXT) && type != '?')
			type = ft_toupper(type);
		return (type);
}

t_symbol	*create_elem(struct nlist_64 symbol, char *name, t_flags flags)
{
	t_symbol 		*new;

	if (!(new = (t_symbol*)malloc(sizeof(t_symbol))))
		return (NULL);
	new->type = get_type(symbol, flags);
	new->name = ft_strdup(name);
	ft_memcpy(&new->symbol, &symbol, sizeof(struct nlist_64));
	new->next = NULL;
	return (new);
}

void		insert_at(t_symbol **list, struct nlist_64 symbol, char *name, t_flags flags)
{
	t_symbol 		*new;
	t_symbol 		*tmp;
	int				(*comp)(t_symbol*, t_symbol*);

	tmp = *list;
	if (!(new = create_elem(symbol, name, flags)))
		return ;
	comp = flags.p ? no_comp : value_comp;
	if (!flags.p && !flags.n)
		comp = name_comp;
	if (!*list)
		*list = new;
	else
	{
		while (tmp && comp(new, tmp) > 0)
		{
			if (!tmp->next || comp(new, tmp->next) <= 0)
			{
				new->next = tmp->next;
				tmp->next = new;			
				return ;
			}
			tmp = tmp->next;
		}
		if (tmp == *list)
		{
			new->next = tmp;
			*list = new;
		}
	}
}

void	print_output(t_symbol *symbols)
{
	t_symbol	*to_del;

	while (symbols)
	{
		if ((symbols->symbol.n_type & N_TYPE) == N_PBUD || (symbols->symbol.n_type & N_TYPE) == N_UNDF)
			ft_printf("%17c", ' ');
		else
			ft_printf("%016llx ",  symbols->symbol.n_value);
		ft_printf("%c ", symbols->type);
		ft_printf("%s\n", symbols->name);
		free(symbols->name);
		to_del = symbols;
		symbols = symbols->next;
		free(to_del);
	}
}

void	organizer(int nsyms, int symoff, int stroff, void *ptr, t_flags flags)
{
	int				i;
	int				y;
	struct nlist_64	*array;
	char			*str_table;
	t_symbol		*symbols;

	i = 0;
	y = 0;
	array = ptr + symoff;
	str_table = ptr + stroff;
	symbols = NULL;
	while (i++ < nsyms)
	{
		if (!(array[i].n_type & N_STAB) || flags.a)
		{
			insert_at(&symbols, array[i], str_table + array[i].n_un.n_strx, flags);
		}
	}
	print_output(symbols);
}

void	get_sects_flags64(struct segment_command_64 *seg, t_flags *flags)
{
	struct section_64	*sect;
	uint32_t			i;

	i = 0;
	sect = (struct section_64 *)((char *)seg + sizeof(struct segment_command_64));
	flags->nb_sects += seg->nsects;
	while (i < seg->nsects)
	{
		if(ft_strcmp((sect + i)->sectname, SECT_TEXT) == 0 &&
		   ft_strcmp((sect + i)->segname, SEG_TEXT) == 0)
		    flags->text_sect = i + 1;
		else if(ft_strcmp((sect + i)->sectname, SECT_DATA) == 0 &&
			ft_strcmp((sect + i)->segname, SEG_DATA) == 0)
		    flags->data_sect = i + 1;
		else if(ft_strcmp((sect + i)->sectname, SECT_BSS) == 0 &&
			ft_strcmp((sect + i)->segname, SEG_DATA) == 0)
		    flags->bss_sect = i + 1;
		i++;
	}
}

void	handle_64(void *ptr, t_flags flags)
{
	int							i;
	int							ncmds;
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct symtab_command		*command;
	
	i = 0;
	header = (struct mach_header_64*)ptr;
	ncmds = header->ncmds;
	lc = ptr + sizeof(struct mach_header_64);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			command = (struct symtab_command*)lc;
			organizer(command->nsyms, command->symoff, command->stroff, ptr, flags);
			break;
		}
		else if (lc->cmd == LC_SEGMENT_64)
			get_sects_flags64((struct segment_command_64*)lc, &flags);
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void	nm(void *ptr, t_flags flags)
{
	unsigned int		magic_number;

	magic_number = *(unsigned int *) ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr, flags);
}

void	too_much(char flag)
{
	ft_printf("flag -%c can appear only 0 or 1 time\n", flag);
	exit(EXIT_FAILURE);
}

void	unknown_flag(char flag)
{
	ft_printf("Unknown command : %c\nUsage : ./ft_nm -parnuU [ files ]\n", flag);
	exit(EXIT_FAILURE);
}

void	parse_flags(char *arg, t_flags *flags)
{
	arg++;
	while (*arg)
	{
		if (*arg == 'p')
			(*flags).p ? too_much(*arg) : (*flags).p++;
		else if (*arg == 'a')
			(*flags).a ? too_much(*arg) : (*flags).a++;
		else if (*arg == 'r')
			(*flags).r ? too_much(*arg) : (*flags).r++;
		else if (*arg == 'n')
			(*flags).n ? too_much(*arg) : (*flags).n++;
		else if (*arg == 'u')
			(*flags).u ? too_much(*arg) : (*flags).u++;
		else if (*arg == 'U')
			(*flags).U ? too_much(*arg) : (*flags).U++;
		else
			unknown_flag(*arg);
		arg++;
	}
}

t_flags	parse_cmd(int ac, char **av)
{
	int		i;
	t_flags	flags;

	i = 0;
	ft_bzero(&flags, sizeof(t_flags*));
	flags.files = (char**)malloc(sizeof(char*) * (ac + 1));
	while (++i < ac)
	{
		if (av[i][0] == '-')
			parse_flags(av[i], &flags);
		else
		{
			flags.nb_files++;
			flags.files[flags.nb_files - 1] = ft_strdup(av[i]);
		}
	}
	if (!flags.nb_files)
	{
		flags.nb_files++;
		flags.files[0] = ft_strdup("a.out");
	}
	flags.files[flags.nb_files] = NULL;
	return (flags);
}

// int		process_files(t_flags flags)
// {

// }

int		main(int ac, char **av)
{
	int			fd;
	int			exit_code;
	struct stat	buf;
	void		*ptr;
	t_flags		flags;

	exit_code = EXIT_SUCCESS;
	flags = parse_cmd(ac, av);
	while (*(flags.files))
	{
		if ((fd = open(*(flags.files), O_RDONLY)) < 0)
		{
			ft_printf("nm: %s: No such file or directory.\n", *(flags.files));
			exit_code = EXIT_FAILURE;
			flags.files++;
			continue;
		}
		if (flags.nb_files > 1)
			ft_printf("\n%s:\n", *(flags.files));
		if (fstat(fd, &buf) > 0)
		{
			perror("fstat");
			return (EXIT_FAILURE);
		}
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		{
			perror("mmap");
			return (EXIT_FAILURE);
		}
		nm(ptr, flags);
		if (munmap(ptr, buf.st_size) < 0)
		{
			perror("munmap");
			return (EXIT_FAILURE);
		}
		flags.files++;
	}
	return (EXIT_SUCCESS);
}
