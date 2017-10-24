#include "ft_nm.h"

t_symbol	*create_elem32(struct nlist symbol, char *name, t_flags flags)
{
	t_symbol		*new;

	if (!(new = (t_symbol*)malloc(sizeof(t_symbol))))
		return (NULL);
	new->type = get_type(symbol.n_type, symbol.n_sect, flags);
	new->name = ft_strdup(name);
	new->value = flags.should_swap ? swap_32(symbol.n_value) : symbol.n_value;
	new->n_sect = symbol.n_sect;
	new->n_type = symbol.n_type;
	new->next = NULL;
	return (new);
}

int			organizer32(int nsyms, int symoff, int stroff, void *ptr, t_flags flags)
{
	int				i;
	uint32_t		offset;
	struct nlist	*array;
	char			*str_table;
	t_symbol		*symbols;
	t_symbol		*new;

	i = 0;
	if (symoff >= flags.file_size || stroff >= flags.file_size)
		return (FILE_CORRUPTED);
	array = ptr + symoff;
	str_table = ptr + stroff;
	symbols = NULL;
	while (i < nsyms)
	{
		if (!(array[i].n_type & N_STAB) || flags.a)
		{
			if ((offset = flags.should_swap ? swap_32(array[i].n_un.n_strx) : array[i].n_un.n_strx) >= flags.file_size - stroff)
				return (FILE_CORRUPTED);
			if (!(new = create_elem32(array[i], str_table + offset, flags)))
				return (MALLOC_ERROR);
			insert_at(&symbols, new, flags);
		}
		i++;
	}
	print_output(symbols, flags);
	return (0);
}

void		get_sects_flags32(struct segment_command *seg, t_flags *flags)
{
	struct section		*sect;
	uint32_t			nsects;
	uint32_t			i;

	i = 0;
	sect = (struct section *)(seg + 1);
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

int		handle_32(void *ptr, t_flags flags)
{
	int							ncmds;
	uint32_t					cmd;
	struct mach_header			*header;
	struct load_command			*lc;
	struct symtab_command		command;

	flags.is_32 = 1;
	header = (struct mach_header*)ptr;
	ncmds = flags.should_swap ? swap_32(header->ncmds) : header->ncmds;
	lc = ptr + sizeof(struct mach_header);
	while (ncmds--)
	{
		cmd = flags.should_swap ? swap_32(lc->cmd) : lc->cmd;
		if (cmd == LC_SYMTAB)
		{
			command = swap_symtab_command((struct symtab_command*)lc, flags);
			return (organizer32(command.nsyms, command.symoff, command.stroff,
				ptr, flags));
		}
		else if (cmd == LC_SEGMENT)
			get_sects_flags32((struct segment_command*)lc, &flags);
		lc = (void *)lc +
			(flags.should_swap ? swap_32(lc->cmdsize) : lc->cmdsize);
	}
	return (NO_SYMTAB);
}
