#include "shellcode.h"

size_t			sh_len_eff(t_shellcode *sh)
{
	if (sh->is_final)
		return (sh->len);
	return (sh->len + 5);
}
