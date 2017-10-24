#include "ft_nm.h"

void	handle_lib(void *ptr, t_flags flags)
{
	int size = ft_atoi(ptr + 56);
	int len;

	len = 0;
	ptr += (size + 68);
	while(*(char*)ptr)
	{
		len = 8 * ((ft_strlen(ptr + 60) - 1) / 8 + 1) + 4;
		size = ft_atoi(ptr + 48);
		nm(ptr + 60 + len, flags);
		ptr += (size + 60);
	}
}