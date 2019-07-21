#include "shellcode.h"

t_bool		sh_xor32(t_shellcode *sh, uint32_t key)
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
	sh->len += 15;
	if (sh_file(sh, "asm_files/xor32") == FALSE)
	{
		sh->len -= 15;
		ft_bzero(sh->content + sh->len, 15);
		return (FALSE);
	}
	return (TRUE);
}
