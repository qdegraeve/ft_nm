#include "ft_nm.h"

int		file_corrupted(t_flags *flags)
{
	write(2, "ft_nm: ", 7);
	ft_putstr_fd(*(flags->files), 2);
	write(2, " The file is corrupted.\n\n", 27);
	flags->exit_code = FILE_CORRUPTED;
	return (flags->exit_code);
}

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
