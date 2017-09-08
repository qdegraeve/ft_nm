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
	uint64_t		res;

	if ((res = sym1->value - sym2->value) == 0)
		return (1);
	else
		return (sym1->value - sym2->value);
}

char	get_type(uint8_t n_type, uint8_t n_sect, t_flags flags)
{
		int type;

		type = n_type & N_TYPE;
		if (type == N_UNDF)
			type = 'u';
		else if (type == N_PBUD)
			type = 'u';
		else if (type == N_ABS)
			type = 'a';
		else if (type == N_SECT)
		{
			if (n_sect == flags.text_sect)
				type = 't';
			else if (n_sect == flags.data_sect)
				type = 'd';
			else if (n_sect == flags.bss_sect)
				type = 'b';
		}
		else if (type == N_INDR)
			type = 'i';
		else
			type = '?';
		if ((n_type & N_EXT) && type != '?')
			type = ft_toupper(type);
		return (type);
}

t_symbol	*create_elem_64(struct nlist_64 symbol, char *name, t_flags flags)
{
	t_symbol 		*new;

	if (!(new = (t_symbol*)malloc(sizeof(t_symbol))))
		return (NULL);
	new->type = get_type(symbol.n_type, symbol.n_sect, flags);
	new->name = ft_strdup(name);
	new->value = (uint64_t)symbol.n_value;
	new->n_sect = symbol.n_sect;
	new->n_type = symbol.n_type;
	new->next = NULL;
	return (new);
}

void		insert_at(t_symbol **list, t_symbol *new, t_flags flags)
{
	t_symbol 		*tmp;
	int				(*comp)(t_symbol*, t_symbol*);

	tmp = *list;
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
		if ((symbols->n_type & N_TYPE) == N_PBUD || (symbols->n_type & N_TYPE) == N_UNDF)
			ft_printf("%17c", ' ');
		else
			ft_printf("%016llx ",  symbols->value);
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
	t_symbol		*new;

	i = 0;
	y = 0;
	array = ptr + symoff;
	str_table = ptr + stroff;
	symbols = NULL;
	while (i < nsyms)
	{
		if (!(array[i].n_type & N_STAB) || flags.a)
		{
			if (!(new = create_elem_64(array[i], str_table + array[i].n_un.n_strx, flags)))
				return ;
			insert_at(&symbols, new, flags);
		}
		i++;
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