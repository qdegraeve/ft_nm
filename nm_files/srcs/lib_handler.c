#include "ft_nm.h"

int		handle_lib(void *ptr, t_flags flags)
{
	int size;
	int len;
	int offset;

	len = 0;
	size = 0;
	if (flags.file_size > 68 && (size = ft_atoi(ptr + 56)) &&
		size + 68 < flags.file_size)
		ptr += (size + 68);
	offset = size + 68;
	flags.is_lib = 1;
	while (size > 0 && *(char*)ptr)
	{
		if (offset + 60 >= flags.file_size ||
			(size = ft_atoi(ptr + 48)) + offset >= flags.file_size)
			return (file_corrupted(&flags));
		len = 8 * ((ft_strlen(ptr + 60) - 1) / 8 + 1) + 4;
		size = ft_atoi(ptr + 48);
		ft_printf("\n%s:(%s):\n", *(flags.files), ptr + 60);
		if (nm(ptr + 60 + len, flags) > 0)
			return (file_corrupted(&flags));
		ptr += (size + 60);
		offset += (size + 60);
	}
	return (!size ? file_corrupted(&flags) : 0);
}
