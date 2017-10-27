#include "ft_nm.h"

static t_symbol	*create_elem32(struct nlist symbol, char *name, t_flags flags)
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

static int		add_to_list32(struct nlist array, t_flags *flags,
	struct symtab_command command, void *ptr)
{
	uint32_t		offset;
	t_symbol		*new;
	char			*str_table;

	str_table = ptr + command.stroff;
	if ((offset = flags->should_swap ? swap_32(array.n_un.n_strx) :
		array.n_un.n_strx) >= flags->file_size - command.stroff)
		return (file_corrupted(flags));
	if (!(new = create_elem32(array, str_table + offset, *flags)))
		return ((flags->exit_code = MALLOC_ERROR));
	if (((new->type == 'u' || new->type == 'U') && flags->u_up) ||
		((new->type != 'u' && new->type != 'U') && flags->u))
		return (0);
	insert_at(&(flags->symbols), new, *flags);
	return (0);
}

static int		organizer32(struct symtab_command command, void *ptr,
	t_flags flags)
{
	uint32_t		i;
	struct nlist	*array;

	i = 0;
	if (command.symoff >= flags.file_size || command.stroff >= flags.file_size)
		return (FILE_CORRUPTED);
	array = ptr + command.symoff;
	while (i < command.nsyms)
	{
		if (!(array[i].n_type & N_STAB) || flags.a)
		{
			if (add_to_list32(array[i], &flags, command, ptr) > 0)
				return (flags.exit_code);
		}
		i++;
	}
	(flags.r && !flags.p) ? print_reverse(flags.symbols, flags) :
		print_output(flags.symbols, flags);
	return (0);
}

static void		get_sects_flags32(struct segment_command *seg, t_flags *flags)
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

int				handle_32(void *ptr, t_flags flags)
{
	int							ncmds;
	uint32_t					cmd;
	struct mach_header			*header;
	struct load_command			*lc;
	struct symtab_command		command;

	header = (struct mach_header*)ptr;
	ncmds = flags.should_swap ? swap_32(header->ncmds) : header->ncmds;
	lc = ptr + sizeof(struct mach_header);
	while (ncmds--)
	{
		cmd = flags.should_swap ? swap_32(lc->cmd) : lc->cmd;
		if (cmd == LC_SYMTAB)
		{
			command = swap_symtab_command((struct symtab_command*)lc, flags);
			return (organizer32(command, ptr, flags));
		}
		else if (cmd == LC_SEGMENT)
			get_sects_flags32((struct segment_command*)lc, &flags);
		if ((lc = (void *)lc + (flags.should_swap ? swap_32(lc->cmdsize) :
			lc->cmdsize)) >= (struct load_command*)(ptr + flags.file_size))
			return (file_corrupted(&flags));
	}
	return (NO_SYMTAB);
}
