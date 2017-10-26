#include "ft_otool.h"

int		file_corrupted(t_flags *flags)
{
	write(2, "ft_nm: ", 7);
	ft_putstr_fd(*(flags->files), 2);
	write(2, " The file is corrupted.\n\n", 27);
	flags->exit_code = FILE_CORRUPTED;
	return (flags->exit_code);
}

int		otool(void *ptr, t_flags flags)
{
	unsigned int		magic_number;

	magic_number = *(unsigned int *)ptr;
	if (magic_number == MH_CIGAM ||
			magic_number == MH_CIGAM_64 ||
			magic_number == FAT_CIGAM)
		flags.should_swap = 1;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		return (handle_64(ptr, flags));
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
	{
		flags.is_32 = 1;
		return (handle_32(ptr, flags));
	}
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		return (handle_fat(ptr, flags));
	else if (ft_strncmp(ARMAG, (char*)ptr, 8) == 0)
		return (handle_lib(ptr, flags));
	else
	{
		write(2, "ft_otool: ", 10);
		ft_putstr_fd(*(flags.files), 2);
		write(2, " The file was not recognized as a valid object file\n", 54);
		return (FILE_NOT_VALID);
	}
}
