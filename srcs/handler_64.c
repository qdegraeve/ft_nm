#include "ft_nm.h"

t_symbol	*create_elem64(struct nlist_64 symbol, char *name, t_flags flags)
{
	t_symbol	*new;

	if (!(new = (t_symbol*)malloc(sizeof(t_symbol))))
		return (NULL);
	new->type = get_type(symbol.n_type, symbol.n_sect, flags);
	new->name = ft_strdup(name);
	new->value = flags.should_swap ? swap_64(symbol.n_value) : symbol.n_value;
	new->n_sect = symbol.n_sect;
	new->n_type = symbol.n_type;
	new->next = NULL;
	return (new);
}

void		organizer64(int nsyms, int symoff, int stroff, void *ptr, t_flags flags)
{
	int				i;
	uint32_t		offset;
	struct nlist_64	*array;
	char			*str_table;
	t_symbol		*symbols;
	t_symbol		*new;

	i = 0;
	array = ptr + symoff;
	str_table = ptr + stroff;
	symbols = NULL;
	while (i < nsyms)
	{
		if (!(array[i].n_type & N_STAB) || flags.a)
		{
			offset = flags.should_swap ? swap_32(array[i].n_un.n_strx) : array[i].n_un.n_strx;
			if (!(new = create_elem64(array[i], str_table + offset, flags)))
				return ;
			insert_at(&symbols, new, flags);
		}
		i++;
	}
	print_output(symbols, flags);
}

void		get_sects_flags64(struct segment_command_64 *seg, t_flags *flags)
{
	struct section_64	*sect;
	uint32_t			nsects;
	uint32_t			i;

	i = 0;
	sect = (struct section_64 *)(seg + 1);
	nsects = flags->should_swap ? swap_32(seg->nsects) : seg->nsects;
	while (i < nsects)
	{
		if (ft_strcmp((sect + i)->sectname, SECT_TEXT) == 0 &&
			ft_strcmp((sect + i)->segname, SEG_TEXT) == 0)
			flags->text_sect = flags->nb_sects + i + 1;
		else if (ft_strcmp((sect + i)->sectname, SECT_DATA) == 0 &&
			ft_strcmp((sect + i)->segname, SEG_DATA) == 0)
			flags->data_sect = flags->nb_sects + i + 1;
		else if (ft_strcmp((sect + i)->sectname, SECT_BSS) == 0)
			flags->bss_sect = flags->nb_sects + i + 1;
		i++;
	}
	flags->nb_sects += nsects;
}

void		handle_64(void *ptr, t_flags flags)
{
	int							ncmds;
	uint32_t					cmd;
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct symtab_command		command;

	header = (struct mach_header_64*)ptr;
	ncmds = flags.should_swap ? swap_32(header->ncmds) : header->ncmds;
	lc = ptr + sizeof(struct mach_header_64);
	while (ncmds--)
	{
		cmd = flags.should_swap ? swap_32(lc->cmd) : lc->cmd;
		if (lc->cmd == LC_SYMTAB)
		{
			command = swap_symtab_command((struct symtab_command*)lc, flags);
			organizer64(command.nsyms, command.symoff, command.stroff,
				ptr, flags);
			break ;
		}
		else if (lc->cmd == LC_SEGMENT_64)
			get_sects_flags64((struct segment_command_64*)lc, &flags);
		lc = (void *)lc +
			(flags.should_swap ? swap_32(lc->cmdsize) : lc->cmdsize);
	}
}
