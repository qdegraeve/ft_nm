#include "ft_nm.h"

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
