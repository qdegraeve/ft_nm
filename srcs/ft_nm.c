#include "ft_nm.h"

char	get_type(struct nlist_64 array)
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
			type = 's';
		else if (type == N_INDR)
			type = 'i';
		else
			type = '?';
		if ((array.n_type & N_EXT) && type != '?')
			type = ft_toupper(type);
		return (type);
}

void	insert_at(t_symbol **list, struct nlist_64 symbol, char *name)
{
	t_symbol 		*new;
	t_symbol 		*tmp;

	tmp = NULL;
	if (!(new = (t_symbol*)malloc(sizeof(t_symbol))))
		return ;
	new->type = get_type(symbol);
	new->name = ft_strdup(name);
	ft_memcpy(&new->symbol, &symbol, sizeof(struct nlist_64));
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

// void	sort_array(struct nlist_64 *array, int nsyms, char *str_table)
// {
// 	struct nlist_64	tmp;
// 	int				i;

// 	i = 1;
// 	tmp = array[i];
// 	while (i < nsyms)
// 	{

// 		if (i + 1 < nsyms && ft_strcmp(array[i].n_un.n_name, array[i + 1].n_un.n_name) > 0)
// 		{
// 			tmp = array[i];
// 			array[i] = array[i + 1];
// 			array[i + 1] = tmp; 
// 			i = 1;
// 			break;
// 		}
// 		i++;
// 	}
// }

void	print_output(int nsyms, int symoff, int stroff, void *ptr)
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
		if (!(array[i].n_type & N_STAB))
		{
			insert_at(&symbols, array[i], str_table + array[i].n_un.n_strx);
		}
	}
	while (symbols)
	{
		if ((symbols->symbol.n_type & N_TYPE) == N_PBUD || (symbols->symbol.n_type & N_TYPE) == N_UNDF)
			ft_printf("%17c", ' ');
		else
			ft_printf("%016llx ",  symbols->symbol.n_value);
		ft_printf("%c ", symbols->type);
		ft_printf("%s\n", symbols->name);
		symbols = symbols->next;
	}
}

void	handle_64(void *ptr)
{
	int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*command;
	// t_list					*lcs;
	
	i = 0;
	header = (struct mach_header_64*)ptr;
	ncmds = header->ncmds;
	lc = ptr + sizeof(struct mach_header_64);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			command = (struct symtab_command*)lc;
			print_output(command->nsyms, command->symoff, command->stroff, ptr);
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void	nm(void *ptr)
{
	unsigned int		magic_number;

	magic_number = *(unsigned int *) ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
}

int		main(int ac, char **av)
{
	int			fd;
	struct stat	buf;
	void		*ptr;

	if (ac != 2)
	{
		ft_printf("please give me only one arg\n");
		return (EXIT_FAILURE);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
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
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
