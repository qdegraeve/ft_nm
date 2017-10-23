#include "ft_nm.h"

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
		else
			type = 's';
	}
	else if (type == N_INDR)
		type = 'i';
	if ((n_type & N_EXT) && type != '?')
		type = ft_toupper(type);
	return (type);
}

void	insert_at(t_symbol **list, t_symbol *new, t_flags flags)
{
	t_symbol		*tmp;
	int				(*comp)(t_symbol*, t_symbol*);

	tmp = *list;
	comp = flags.p ? no_comp : value_comp;
	if (!flags.p && !flags.n)
		comp = name_comp;
	if (!*list)
		*list = new;
	else
	{
		while (tmp && (comp(new, tmp)) > 0)
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

void	print_output(t_symbol *symbols, t_flags flags)
{
	t_symbol	*to_del;
	int			size;

	size = flags.is_32 ? 8 : 16;
	if (!flags.is_fat)
		ft_printf("\n%s:\n", *(flags.files));
	while (symbols)
	{
		if ((symbols->n_type & N_TYPE) == N_PBUD ||
				(symbols->n_type & N_TYPE) == N_UNDF)
			ft_printf("%*c ", size, ' ');
		else
			ft_printf("%0*llx ", size, symbols->value);
		ft_printf("%c ", symbols->type);
		ft_printf("%s\n", symbols->name);
		free(symbols->name);
		to_del = symbols;
		symbols = symbols->next;
		free(to_del);
	}
}

void	nm(void *ptr, t_flags flags)
{
	unsigned int		magic_number;

	magic_number = *(unsigned int *)ptr;
	if (magic_number == MH_CIGAM ||
			magic_number == MH_CIGAM_64 ||
			magic_number == FAT_CIGAM)
		flags.should_swap = 1;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		handle_64(ptr, flags);
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		handle_32(ptr, flags);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		handle_fat(ptr, flags);
	else if (ft_strncmp(ARMAG, (char*)ptr, 8) == 0)
		handle_lib(ptr, flags);
	else
	{
		write(2, "ft_nm: ", 7);
		ft_putstr_fd(*(flags.files), 2);
		write(2, " The file was not recognized as a valid object file\n\n", 54);
	}
}
