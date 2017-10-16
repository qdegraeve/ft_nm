#include "ft_nm.h"

char	*cputype_to_a(int cputype)
{
	if (cputype == CPU_TYPE_POWERPC)
		return ("ppc");
	else if (cputype == CPU_TYPE_I386)
		return ("i386");
	return ("unknown");
}

void	handle_fat(void *ptr, t_flags flags)
{
	unsigned int		nfat_arch;
	unsigned int		i;
	struct fat_arch		*fat_arch;

	i = 0;
	nfat_arch = swap_uint32(((struct fat_header*)ptr)->nfat_arch);
	fat_arch = (struct fat_arch*)(((struct fat_header*)ptr) + 1);
	while (i < nfat_arch)
	{
		ft_printf("%s (for architecture %s)\n", flags.files[flags.file_offset], cputype_to_a(swap_uint32(fat_arch->cputype)));
		nm((void*)ptr + (swap_uint32(fat_arch->offset)), flags);
		fat_arch++;
		if (++i < nfat_arch)
			write(1, "\n", 1);
	}
}