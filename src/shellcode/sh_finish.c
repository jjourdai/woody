#include "shellcode.h"
#include "woody.h"
#include "libft.h"

void		sh_finish(t_shellcode *sh, t_shellcode_meta meta)
{
	printf("%x\n", meta.entrypoint);
	printf("%lx\n", meta.vmaddr_text_ptr);
	printf("%lx\n", meta.vmaddr_text_len);
	printf("%lx\n", sh->len - 17);
	ft_memcpy(sh->content + sh->off_entrypoint, &meta.entrypoint, 4);
//	int val = meta.entrypoint + (sh->len - 17);
	int val = meta.section_text_offset + (sh->len - 17);
	printf("%lx\n", val);
	for (size_t i = 0; i < COUNT_OF(sh->off_vmaddr_text_ptr); ++i)
	{
		if (sh->off_vmaddr_text_ptr[i] != 0)
			ft_memcpy(sh->content + sh->off_vmaddr_text_ptr[i], &val, 4);
	}
	for (size_t i = 0; i < COUNT_OF(sh->off_vmaddr_text_len); ++i)
	{
		if (sh->off_vmaddr_text_len[i] != 0)
			ft_memcpy(sh->content + sh->off_vmaddr_text_len[i], &meta.vmaddr_text_len, 4);
	}
}
