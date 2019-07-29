#include "woody.h"
#include "encrypt.h"

t_bool		sh_xor(t_shellcode *sh, uint32_t key, enum xor_size size)
{
	(void)size;
	sh->content[sh->len++] = 0x48;
	sh->content[sh->len++] = 0x8d;
	sh->content[sh->len++] = 0x3d;
	sh->off_vmaddr_text_ptr = sh->len;
	sh->len += 4;
	sh->content[sh->len++] = 0xba;
	ft_memcpy(sh->content + sh->len, &key, 4);
	sh->len += 4;
	sh->content[sh->len++] = 0xbe;
	sh->off_vmaddr_text_len = sh->len;
	sh->len += 4;
	if (sh_file(sh, g_env.asm_file) == FALSE)
		__FATAL(SECTION_TEXT_NOT_FOUND, BINARY_NAME, "Not found");
	return (TRUE);
}
