#include "ft_otool.h"

static void		print_content(struct section_64 *sect, void *ptr,
	t_flags *flags)
{
	uint64_t	size;
	uint32_t	offset;
	uint64_t	addr;
	uint64_t	i;

	i = 0;
	size = flags->should_swap ? swap_64(sect->size) : sect->size;
	offset = flags->should_swap ? swap_32(sect->offset) : sect->offset;
	addr = flags->should_swap ? swap_64(sect->addr) : sect->addr;
	if (!flags->is_lib && !flags->is_fat)
		ft_printf("%s:\n", *(flags->files));
	ft_printf("Contents of (%s,%s) section", sect->segname, sect->sectname);
	while (i < size)
	{
		if (i % 16 == 0)
			ft_printf("\n%016lx\t", (sect->addr + i), ' ');
		ft_printf("%02x ", *((char*)ptr + offset + i) & SECTION_TYPE);
		i++;
	}
	write(1, "\n", 1);
}

static void		get_sects_flags64(struct segment_command_64 *seg,
	t_flags *flags, void *ptr)
{
	struct section_64	*sect;
	uint32_t			nsects;
	uint32_t			i;

	i = 0;
	sect = (struct section_64 *)(seg + 1);
	nsects = flags->should_swap ? swap_32(seg->nsects) : seg->nsects;
	while (i < nsects)
	{
		if (ft_strcmp((sect + i)->sectname, SECT_TEXT) == 0 &&
			ft_strcmp((sect + i)->segname, SEG_TEXT) == 0)
			print_content((sect + i), ptr, flags);
		else if (ft_strcmp((sect + i)->sectname, SECT_DATA) == 0 &&
			ft_strcmp((sect + i)->segname, SEG_DATA) == 0 && flags->d)
			print_content((sect + i), ptr, flags);
		i++;
	}
}

int				handle_64(void *ptr, t_flags flags)
{
	int							ncmds;
	uint32_t					cmd;
	struct mach_header_64		*header;
	struct load_command			*lc;

	header = (struct mach_header_64*)ptr;
	ncmds = flags.should_swap ? swap_32(header->ncmds) : header->ncmds;
	lc = ptr + sizeof(struct mach_header_64);
	while (ncmds--)
	{
		cmd = flags.should_swap ? swap_32(lc->cmd) : lc->cmd;
		if (lc->cmd == LC_SEGMENT_64)
			get_sects_flags64((struct segment_command_64*)lc, &flags, ptr);
		if ((lc = (void *)lc + (flags.should_swap ? swap_32(lc->cmdsize) :
			lc->cmdsize)) >= (struct load_command*)(ptr + flags.file_size))
			return (file_corrupted(&flags));
	}
	return (0);
}
