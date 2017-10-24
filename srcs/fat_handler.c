#include "ft_nm.h"

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
	if (!fat)
	{
		flags->nfat_arch = 0;
		flags->file_size = 0;
	}
	flags->is_32 = 0;
	flags->should_swap = 0;
	flags->text_sect = 0;
	flags->data_sect = 0;
	flags->bss_sect = 0;
	flags->nb_sects = 0;
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

	i = 0;
	while (i++ < nfat_arch)
	{
		if (flags.cputype == (cpu_type_t)swap_32(fat_arch->cputype))
		{
			reset_flags(&flags, 1);
			flags.nfat_arch = 1;
			nm((void*)ptr + (swap_32(fat_arch->offset)), flags);
			return (1);
		}
		fat_arch++;
	}
	return (0);
}

int					handle_fat(void *ptr, t_flags flags)
{
	unsigned int		i;
	struct fat_arch		*fat_arch;

	i = 0;
	flags.nfat_arch = swap_32(((struct fat_header*)ptr)->nfat_arch);
	fat_arch = (struct fat_arch*)(((struct fat_header*)ptr) + 1);
	if (look_for_arch(fat_arch, ptr, flags.nfat_arch, flags))
		return (0);
	while (i++ < flags.nfat_arch)
	{
		reset_flags(&flags, 1);
		if (flags.nfat_arch > 1)
			write(1, "\n", 1);
		ft_putstr(*(flags.files));
		if (flags.nfat_arch > 1)
			ft_printf(" (for architecture %s)",
				cpu_type_name(swap_32(fat_arch->cputype)));
		write(1, ":\n", 2);
		nm((void*)ptr + (swap_32(fat_arch->offset)), flags);
		fat_arch++;
	}
	return (0);
}
