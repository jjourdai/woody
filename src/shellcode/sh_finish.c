#include "shellcode.h"
#include "woody.h"
#include "libft.h"

void		sh_finish(t_shellcode *sh, uint32_t addr)
{
	for (size_t i = 0; i < COUNT_OF(sh->tab_textptr); ++i)
	{
		ft_memcpy(sh->content + sh->tab_textptr[i], &addr, 4);
	}
}
