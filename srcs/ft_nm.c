#include <stdio.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

void	print_output(int nsyms, int symoff, int stroff, void *ptr)
{
	int				i;
	struct nlist_64	*array;
	char			*str_table;

	i = 0;
	array = ptr + symoff;
	str_table = ptr + stroff;
	while (i++ < nsyms)
	{
		if ((array[i].n_type & N_STAB))
		{
		
		printf("  %016llx %u  ", array[i].n_value, (array[i].n_type ^ N_TYPE));
		printf("%s\n", str_table + array[i].n_un.n_strx);
		}
	}
}

void	handle_64(void *ptr)
{
	int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*command;
	
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
		fprintf(stderr, "please give me only one arg\n");
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
