#include "shellcode.h"
#include "woody.h"
#include "libft.h"

void		sh_finish(t_shellcode *sh, t_shellcode_meta meta)
{
/*
	printf("%x\n", meta.entrypoint);
	printf("%x\n", meta.vmaddr_text_ptr);
	printf("%x\n", meta.vmaddr_text_len);
	printf("%lx\n", sh->len - 17);
*/
	ft_memcpy(sh->content + sh->off_entrypoint, &meta.entrypoint, 4);
//	int val = meta.entrypoint + (sh->len - 17);
	int val = meta.section_text_offset + (sh->len - 17);
	if (sh->off_vmaddr_text_ptr != 0)
		ft_memcpy(sh->content + sh->off_vmaddr_text_ptr, &val, 4);
	if (sh->off_vmaddr_text_len != 0)
		ft_memcpy(sh->content + sh->off_vmaddr_text_len, &meta.vmaddr_text_len, 4);
}
