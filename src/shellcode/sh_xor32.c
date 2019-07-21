#include "shellcode.h"

void		sh_xor32(t_shellcode *sh, uint32_t key)
{
	sh->content[sh->len + 0] = 0xbf;
	sh->off_vmaddr_text_ptr[0] = sh->len + 1;
	sh->content[sh->len + 5] = 0xbe;
	sh->off_vmaddr_text_len[0] = sh->len + 6;
	sh->content[sh->len + 10] = 0xba;
	sh->content[sh->len + 11] = (key >> 24) & 0xFF;
	sh->content[sh->len + 12] = (key >> 16) & 0xFF;
	sh->content[sh->len + 13] = (key >> 8) & 0xFF;
	sh->content[sh->len + 14] = (key >> 0) & 0xFF;
	sh->content[sh->len + 15] = 0x48;
	sh->content[sh->len + 16] = 0x89;
	sh->content[sh->len + 17] = 0xF1;
	sh->content[sh->len + 18] = 0x48;
	sh->content[sh->len + 19] = 0x83;
	sh->content[sh->len + 20] = 0xF9;
	sh->content[sh->len + 21] = 0x04;

	sh->content[sh->len + 22] = 0x7C;
	sh->content[sh->len + 23] = 0x0C;

	sh->content[sh->len + 24] = 0x67;
	sh->content[sh->len + 25] = 0x31;
	sh->content[sh->len + 26] = 0x17;

	sh->content[sh->len + 27] = 0x83;
	sh->content[sh->len + 28] = 0xC7;
	sh->content[sh->len + 29] = 0x04;

	sh->content[sh->len + 30] = 0x48;
	sh->content[sh->len + 31] = 0x83;
	sh->content[sh->len + 32] = 0xE9;
	sh->content[sh->len + 33] = 0x04;

	sh->content[sh->len + 34] = 0xEB;
	sh->content[sh->len + 35] = 0xEF;
	sh->len += 36;
}
