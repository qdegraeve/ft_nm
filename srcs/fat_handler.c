#include "ft_nm.h"

static t_cpu_type_names		g_cpu_type_names[] = {
	{ CPU_TYPE_I386, "i386" },
	{ CPU_TYPE_X86_64, "x86_64" },
	{ CPU_TYPE_ARM, "arm" },
	{ CPU_TYPE_ARM64, "arm64" },
	{ CPU_TYPE_POWERPC, "ppc" }
};

void				reset_flags(t_flags *flags)
{
	flags->is_32 = 0;
	flags->should_swap = 0;
	flags->text_sect = 0;
	flags->data_sect = 0;
	flags->bss_sect = 0;
	flags->nb_sects = 0;
	flags->sects = NULL;
	flags->sects64 = NULL;
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
		if (!ft_strcmp(flags.arch, cpu_type_name(swap_32(fat_arch->cputype))))
		{
			reset_flags(&flags);
			nm((void*)ptr + (swap_32(fat_arch->offset)), flags);
			return (1);
		}
		fat_arch++;
	}
	return (0);
}

void				handle_fat(void *ptr, t_flags flags)
{
	unsigned int		nfat_arch;
	unsigned int		i;
	struct fat_arch		*fat_arch;

	i = 0;
	nfat_arch = swap_32(((struct fat_header*)ptr)->nfat_arch);
	fat_arch = (struct fat_arch*)(((struct fat_header*)ptr) + 1);
	if (look_for_arch(fat_arch, ptr, nfat_arch, flags))
		return ;
	while (i++ < nfat_arch)
	{
		ft_printf("\n%s (for architecture %s):\n",
			flags.files[flags.file_offset],
			cpu_type_name(swap_32(fat_arch->cputype)));
		reset_flags(&flags);
		nm((void*)ptr + (swap_32(fat_arch->offset)), flags);
		fat_arch++;
	}
}
