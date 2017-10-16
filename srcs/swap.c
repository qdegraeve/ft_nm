#include "ft_nm.h"

uint16_t		swap_uint16(uint16_t to_swap)
{
	return ((to_swap << 8) | (to_swap >> 8));
}

uint32_t		swap_uint32(uint32_t to_swap)
{
	uint32_t	swapped;

	swapped = ((to_swap >> 24) & 0xff) |
		((to_swap >> 8) & 0xff00) |
		((to_swap << 8) & 0xff0000) |
		((to_swap << 24) & 0xff000000);
	return(swapped);
}