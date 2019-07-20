#include "shellcode.h"

void	sh_initframe(t_shellcode *sh)
{
	sh->content[sh->len + 0] = 0x55; // push rbp
	sh->content[sh->len + 1] = 0x48;
	sh->content[sh->len + 2] = 0x89;
	sh->content[sh->len + 3] = 0xe5; // mov rbp, rsp
	sh->len += 4;
}
