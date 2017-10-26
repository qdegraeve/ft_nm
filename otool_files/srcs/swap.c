#include "ft_otool.h"

uint16_t				swap_16(uint16_t to_swap)
{
	return ((to_swap << 8) | (to_swap >> 8));
}

uint32_t				swap_32(uint32_t to_swap)
{
	uint32_t	swapped;

	swapped = ((to_swap >> 24) & 0xff) |
		((to_swap >> 8) & 0xff00) |
		((to_swap << 8) & 0xff0000) |
		((to_swap << 24) & 0xff000000);
	return (swapped);
}

uint64_t				swap_64(uint64_t to_swap)
{
	uint64_t	swapped;

	swapped = ((to_swap >> 56) & 0xff) |
		((to_swap >> 40) & 0xff00) |
		((to_swap >> 24) & 0xff0000) |
		((to_swap >> 8) & 0xff000000) |
		((to_swap << 8) & 0xff00000000) |
		((to_swap << 24 & 0xff00000000)) |
		((to_swap << 40) & 0xff000000000000) |
		((to_swap << 56) & 0xff00000000000000);
	return (swapped);
}

struct symtab_command	swap_symtab_command(
	struct symtab_command *sc, t_flags flags)
{
	struct symtab_command		new;

	new.symoff = flags.should_swap ? swap_32(sc->symoff) : sc->symoff;
	new.nsyms = flags.should_swap ? swap_32(sc->nsyms) : sc->nsyms;
	new.stroff = flags.should_swap ? swap_32(sc->stroff) : sc->stroff;
	new.strsize = flags.should_swap ? swap_32(sc->strsize) : sc->strsize;
	return (new);
}
