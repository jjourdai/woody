#include "shellcode.h"

void			sh_regs_save(t_shellcode *sh)
{
	sh->content[sh->len + 0] = 0x50; // push rax
	sh->content[sh->len + 1] = 0x53; // push rbx
	sh->content[sh->len + 2] = 0x51; // push rcx
	sh->content[sh->len + 3] = 0x52; // push rdx
	sh->content[sh->len + 4] = 0x57; // push rdi
	sh->content[sh->len + 5] = 0x56; // push rsi
	sh->len += 6;
}
