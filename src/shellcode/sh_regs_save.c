#include "shellcode.h"

void			sh_regs_save(t_shellcode *sh)
{
	sh->content[sh->len + 0] = PUSH_RAX;
	sh->content[sh->len + 1] = PUSH_RBX;
	sh->content[sh->len + 2] = PUSH_RCX;
	sh->content[sh->len + 3] = PUSH_RDX;
	sh->content[sh->len + 4] = PUSH_RDI;
	sh->content[sh->len + 5] = PUSH_RSI;
	sh->len += 6;
}
