#include "ft_nm.h"

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
		else if (*arg == 'j')
			(*flags).j ? too_much(*arg) : (*flags).j++;
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
			flags.files[flags.nb_files - 1] = av[i];
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

int		open_file(void **ptr, t_flags *flags)
{
	int			fd;
	struct stat	buf;

	if ((fd = open(*(flags->files), O_RDONLY)) < 0)
	{
		write(2, "ft_nm: ", 6);
		ft_putstr_fd(*(flags->files), 2);
		write(2, " No such file or directory.\n", 28);
		flags->exit_code = OPEN_ERROR;
		flags->files++;
		if (*(flags->files))
			return (open_file(ptr, flags));
		else
			return (flags->exit_code);
	}
	if (fstat(fd, &buf) > 0)
		return (FSTAT_ERROR);
	if ((*ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (MMAP_ERROR);
	flags->file_size = buf.st_size;
	return (0);
}

int		main(int ac, char **av, char **env)
{
	void		*ptr;
	char		**tmp;
	t_flags		flags;

	flags = parse_cmd(ac, av);
	tmp = flags.files;
	flags.cputype = cpu_type(find_arch(env));
	ptr = NULL;
	while (*flags.files)
	{
		if (open_file(&ptr, &flags) > 0)
			return (flags.exit_code);
		flags.exit_code = nm(ptr, flags);
		if (munmap(ptr, flags.file_size) < 0)
		{
			return (MUNMAP_ERROR);
		}
		reset_flags(&flags, 0);
		flags.files++;
	}
	free(tmp);
	return (flags.exit_code);
}
