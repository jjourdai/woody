#include "shellcode.h"
#include "libft.h"

void			sh_print(t_shellcode *sh, const char *str, uint8_t len)
{
	sh->content[sh->len + 0] = 0xe8; // call
	sh->content[sh->len + 1] = len;
	sh->content[sh->len + 2] = 0;
	sh->content[sh->len + 3] = 0;
	sh->content[sh->len + 4] = 0;
	ft_memcpy(sh->content + sh->len + 5, str, len);
	sh->len += len + 5;
	ft_bzero(sh->content + sh->len, 18);
	sh->content[sh->len + 0] = 0xbf; // move edi
	sh->content[sh->len + 1] = 0x01; // STDOUT
	sh->content[sh->len + 5] = 0x5e; // pop rsi -> put the string in rsi
	sh->content[sh->len + 6] = 0xba; // move edx
	sh->content[sh->len + 7] = len; // put len
	sh->content[sh->len + 11] = 0xb8; // move rax
	sh->content[sh->len + 12] = 0x01; // syscall write
	sh->content[sh->len + 16] = 0x0f;
	sh->content[sh->len + 17] = 0x05;
	sh->len += 18;
}
