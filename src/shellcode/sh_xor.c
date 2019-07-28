#include "woody.h"
#include "encrypt.h"

t_bool		sh_xor(t_shellcode *sh, uint32_t key, enum xor_size size)
{
	sh->content[sh->len++] = 0x48;
	sh->content[sh->len++] = 0x8d;
	sh->content[sh->len++] = 0x3d;
	sh->off_vmaddr_text_ptr[0] = sh->len;
	sh->len += 4;
	sh->content[sh->len++] = 0xba;
/*
	int shift = (size - 1) * 8;
	for (uint8_t i = 0; i < 4; i++) {
		sh->content[sh->len++] = (shift >= 0) ? (key >> shift) & 0xFF : 0;
		shift -= 8;
	}
*/
	ft_memcpy(sh->content + sh->len, &key, 4);
	sh->len += 4;
	sh->content[sh->len++] = 0xbe;
	sh->off_vmaddr_text_len[0] = sh->len;
	sh->len += 4;
	if (sh_file(sh, g_env.asm_file) == FALSE)
		return (FALSE);
	return (TRUE);
}
