#include "shellcode.h"
#include "libft.h"
#include "woody.h"

void	sh_jump(t_shellcode *sh)
{
	if (sh->tab_textptr[0] != (size_t)-1)
		return ;
	sh->content[sh->len + 0] = 0xe9;
	sh->tab_textptr[0] = sh->len + 1;
	sh->len += 5;
}
