#include "shellcode.h"
#include "woody.h"
#include "libft.h"

void		sh_test(t_shellcode *sh)
{
	static int i = 0;

	sh->content[sh->len + 0] = 0x8b;
	sh->content[sh->len + 1] = 0x05;
	sh->content[sh->len + 2] = 0x07;
	sh->content[sh->len + 6] = 0x35;
	sh->content[sh->len + 7] = 0x78;
	sh->content[sh->len + 8] = 0x56;
	sh->content[sh->len + 9] = 0x34;
	sh->content[sh->len + 10] = 0x12;
	sh->content[sh->len + 11] = 0xeb;
	sh->content[sh->len + 12] = 0x08;
	sh->off_vmaddr_text_ptr[i++] = sh->len + 13;
	sh->len += 21;
}

void		sh_finish(t_shellcode *sh, t_shellcode_meta meta)
{
	// printf("%x\n", meta.entrypoint);
	// printf("%lx\n", meta.vmaddr_text_ptr);
	// printf("%lx\n", meta.vmaddr_text_len);
	ft_memcpy(sh->content + sh->off_entrypoint, &meta.entrypoint, 4);
	for (size_t i = 0; i < COUNT_OF(sh->off_vmaddr_text_ptr); ++i)
	{
		if (sh->off_vmaddr_text_ptr[i] != 0)
			ft_memcpy(sh->content + sh->off_vmaddr_text_ptr[i], &meta.vmaddr_text_ptr, 8);
	}
	for (size_t i = 0; i < COUNT_OF(sh->off_vmaddr_text_len); ++i)
	{
		if (sh->off_vmaddr_text_len[i] != 0)
			ft_memcpy(sh->content + sh->off_vmaddr_text_len[i], &meta.vmaddr_text_len, 8);
	}
}
