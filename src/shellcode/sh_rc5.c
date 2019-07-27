#include "woody.h"
#include "encrypt.h"

t_bool		sh_rc5(t_shellcode *sh, uint8_t rc5[KEY_SIZE])
{
	uint32_t	tmp;
	
	sh->content[sh->len++] = 0x48;
	sh->content[sh->len++] = 0x8d;
	sh->content[sh->len++] = 0x3d;
	sh->off_vmaddr_text_ptr[0] = sh->len;
	sh->len += 4;
	sh->content[sh->len++] = 0xbe;
	sh->off_vmaddr_text_len[0] = sh->len;
	sh->len += 4;
	sh->content[sh->len++] = 0xe8;
	tmp = KEY_SIZE;
	ft_memcpy(sh->content + sh->len, &tmp, 4);
	sh->len += 4;
	ft_memcpy(sh->content + sh->len, rc5, KEY_SIZE);
	sh->len += KEY_SIZE;
	sh->content[sh->len++] = 0x5a;
	sh->content[sh->len++] = 0xb9;
	tmp = NB_ROUNDS;
	ft_memcpy(sh->content + sh->len, &tmp, 4);
	sh->len += 4;
	if (sh_file(sh, g_env.asm_file) == FALSE)
		return (FALSE);
	return (TRUE);
}
