#include "shellcode.h"

void			sh_regs_recover(t_shellcode *sh)
{
	sh->content[sh->len + 0] = POP_RSI;
	sh->content[sh->len + 1] = POP_RDI;
	sh->content[sh->len + 2] = POP_RDX;
	sh->content[sh->len + 3] = POP_RCX;
	sh->content[sh->len + 4] = POP_RBX;
	sh->content[sh->len + 5] = POP_RAX;
	sh->len += 6;
}
