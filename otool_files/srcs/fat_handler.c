#include "ft_otool.h"

static t_cpu_type_names		g_cpu_type_names[] = {
	{ CPU_TYPE_I386, "i386" },
	{ CPU_TYPE_X86_64, "x86_64" },
	{ CPU_TYPE_ARM, "arm" },
	{ CPU_TYPE_ARM64, "arm64" },
	{ CPU_TYPE_POWERPC, "ppc" }
};

void				reset_flags(t_flags *flags, char fat)
{
	flags->is_fat = fat;
	flags->is_lib = 0;
	if (!fat)
	{
		flags->nfat_arch = 0;
		flags->file_size = 0;
	}
	flags->is_32 = 0;
	flags->should_swap = 0;
}

cpu_type_t			cpu_type(char *cpu_type_name)
{
	static int	cpu_type_names_size;
	int			i;

	cpu_type_names_size = sizeof(g_cpu_type_names) / sizeof(t_cpu_type_names);
	i = 0;
	while (i < cpu_type_names_size)
	{
		if (ft_strcmp(cpu_type_name, g_cpu_type_names[i].cpu_name) == 0)
			return (g_cpu_type_names[i].cputype);
		i++;
	}
	return (0);
}

static const char	*cpu_type_name(cpu_type_t cpu_type)
{
	static int	cpu_type_names_size;
	int			i;

	cpu_type_names_size = sizeof(g_cpu_type_names) / sizeof(t_cpu_type_names);
	i = 0;
	while (i < cpu_type_names_size)
	{
		if (cpu_type == g_cpu_type_names[i].cputype)
			return (g_cpu_type_names[i].cpu_name);
		i++;
	}
	return ("unknown");
}

int					look_for_arch(struct fat_arch *fat_arch,
	void *ptr, unsigned int nfat_arch, t_flags flags)
{
	unsigned int		i;
	uint32_t			offset;

	i = 0;
	offset = 0;
	while (i++ < nfat_arch)
	{
		if (flags.cputype == (cpu_type_t)swap_32(fat_arch->cputype))
		{
			reset_flags(&flags, 1);
			flags.is_fat = 0;
			if ((offset = swap_32(fat_arch->offset)) < flags.file_size)
				otool((void*)ptr + offset, flags);
			else
				file_corrupted(&flags);
			return (1);
		}
		fat_arch++;
	}
	return (0);
}

int					handle_fat(void *ptr, t_flags fgs)
{
	unsigned int		i;
	struct fat_arch		*fat_arch;
	uint32_t			offset;

	i = 0;
	offset = 0;
	fgs.nfat_arch = swap_32(((struct fat_header*)ptr)->nfat_arch);
	fat_arch = (struct fat_arch*)(((struct fat_header*)ptr) + 1);
	if (look_for_arch(fat_arch, ptr, fgs.nfat_arch, fgs))
		return (0);
	while (i++ < fgs.nfat_arch && fgs.exit_code == 0)
	{
		reset_flags(&fgs, 1);
		(fgs.nfat_arch > 1) ? write(1, "\n", 1) : 0;
		ft_putstr(*(fgs.files));
		if (fgs.nfat_arch > 1)
			ft_printf(" (for architecture %s)",
				cpu_type_name(swap_32(fat_arch->cputype)));
		write(1, ":\n", 2);
		if ((offset += swap_32(fat_arch->offset)) >= fgs.file_size)
			return (file_corrupted(&fgs));
		fgs.exit_code = otool((void*)ptr + (swap_32(fat_arch->offset)), fgs);
		fat_arch++;
	}
	return (fgs.exit_code);
}
