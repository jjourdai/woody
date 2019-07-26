#include "shellcode.h"

void	sh_initframe(t_shellcode *sh)
{
	sh->content[sh->len + 0] = 0x55; // push rbp
	sh->content[sh->len + 1] = 0x48;
	sh->content[sh->len + 2] = 0x89;
	sh->content[sh->len + 3] = 0xe5; // mov rbp, rsp
	// sh->content[sh->len + 4] = 0x48;
	// sh->content[sh->len + 5] = 0x83;
	// sh->content[sh->len + 6] = 0xe4;
	// sh->content[sh->len + 7] = 0xf0; // and rsp, -16
	// sh->len += 8;
	sh->len += 4;
}
