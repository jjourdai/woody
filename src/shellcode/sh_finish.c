#include "shellcode.h"
#include "woody.h"
#include "libft.h"

void		sh_finish(t_shellcode *sh, t_shellcode_meta meta)
{
	// printf("%x\n", meta.entrypoint);
	// printf("%lx\n", meta.vmaddr_text_ptr);
	// printf("%lx\n", meta.vmaddr_text_len);
	ft_memcpy(sh->content + sh->off_entrypoint, &meta.entrypoint, 4);
	for (size_t i = 0; i < COUNT_OF(sh->off_vmaddr_text_ptr); ++i)
	{
		if (sh->off_vmaddr_text_ptr[i] != 0)
			ft_memcpy(sh->content + sh->off_vmaddr_text_ptr[i], &meta.vmaddr_text_ptr, 4);
	}
	for (size_t i = 0; i < COUNT_OF(sh->off_vmaddr_text_len); ++i)
	{
		if (sh->off_vmaddr_text_len[i] != 0)
			ft_memcpy(sh->content + sh->off_vmaddr_text_len[i], &meta.vmaddr_text_len, 4);
	}
}
