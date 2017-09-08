#include "ft_nm.h"

int		no_comp(t_symbol *sym1, t_symbol *sym2)
{
	sym1 = NULL;
	sym2 = NULL;
	return (1);
}

int		name_comp(t_symbol *sym1, t_symbol *sym2)
{
	return (ft_strcmp(sym1->name, sym2->name));
}

int		value_comp(t_symbol *sym1, t_symbol *sym2)
{
	uint64_t		res;

	if ((res = sym1->value - sym2->value) == 0)
		return (1);
	else
		return (sym1->value - sym2->value);
}