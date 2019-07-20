#include "shellcode.h"
#include "libft.h"
#include "woody.h"

void	sh_final_jump(t_shellcode *sh, uint32_t addr)
{
	if (sh->is_final)
		return ;
	sh->content[sh->len + 0] = 0xe9;
	ft_memcpy(sh->content + sh->len + 1, &addr, 4);
	sh->len += 5;
	sh->is_final = TRUE;
}
