#include "shellcode.h"

void			sh_regs_recover(t_shellcode *sh)
{
	sh->content[sh->len + 0] = 0x5e; // pop rsi
	sh->content[sh->len + 1] = 0x5f; // pop rdi
	sh->content[sh->len + 2] = 0x5a; // pop rdx
	sh->content[sh->len + 3] = 0x59; // pop rcx
	sh->content[sh->len + 4] = 0x5b; // pop rbx
	sh->content[sh->len + 5] = 0x58; // pop rax
	sh->len += 6;
}
