#include "ft_nm.h"

void	too_much(char flag)
{
	ft_printf("flag -%c can appear only 0 or 1 time\n", flag);
	exit(EXIT_FAILURE);
}

void	unknown_flag(char flag)
{
	ft_printf("Unknown command : %c\nUsage : ./ft_nm -parnuU [ files ]\n",
		flag);
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
			(*flags).u_up ? too_much(*arg) : (*flags).u_up++;
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
	flags.files = (char**)malloc(sizeof(char*) * (ac));
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

char	*find_arch(char **env)
{
	while (*env)
	{
		if (ft_strncmp(*env, "_system_arch", 12) == 0)
			return (*env + 13);
		env++;
	}
	return ("");
}

int		main(int ac, char **av, char **env)
{
	int			fd;
	int			exit_code;
	int			i;
	struct stat	buf;
	void		*ptr;
	char		**tmp;
	t_flags		flags;

	i = -1;
	exit_code = EXIT_SUCCESS;
	flags = parse_cmd(ac, av);
	tmp = flags.files;
	flags.cputype = cpu_type(find_arch(env));
	while (++i < flags.nb_files)
	{
		if ((fd = open(*(flags.files), O_RDONLY)) < 0)
		{
			write(2, "ft_nm: ", 6);
			ft_putstr_fd(*(flags.files), 2);
			write(2, " No such file or directory.\n", 28);
			exit_code = EXIT_FAILURE;
			flags.files++;
			continue;
		}
		if (fstat(fd, &buf) > 0)
		{
			perror("fstat");
			return (EXIT_FAILURE);
		}
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
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
		reset_flags(&flags, 0);
		ft_strdel((flags.files));
		flags.files++;
	}
	free(tmp);
	return (EXIT_SUCCESS);
}
