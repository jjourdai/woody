#include "shellcode.h"

void	sh_endframe(t_shellcode *sh)
{
	sh->content[sh->len + 0] = 0x48;
	sh->content[sh->len + 1] = 0x89;
	sh->content[sh->len + 2] = 0xec; // mov rsp, rbp
	sh->content[sh->len + 3] = 0x5d; // pop rbp
	sh->len += 4;
}
