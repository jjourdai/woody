#include "shellcode.h"
#include "libft.h"
#include "woody.h"

void	sh_jump(t_shellcode *sh)
{
	sh->content[sh->len + 0] = 0xe9;
	sh->off_entrypoint = sh->len + 1;
	sh->len += 5;
}
