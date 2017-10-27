#include "ft_otool.h"

int		file_corrupted(t_flags *flags)
{
	write(2, "ft_otool: ", 7);
	ft_putstr_fd(*(flags->files), 2);
	write(2, " The file is corrupted.\n\n", 27);
	flags->exit_code = FILE_CORRUPTED;
	return (flags->exit_code);
}

void	unknown_flag(char flag)
{
	ft_printf("Unknown command : %c\nUsage : ./ft_otool -td [ files ]\n",
		flag);
	exit(EXIT_FAILURE);
}
