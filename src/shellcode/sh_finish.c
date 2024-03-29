#include "shellcode.h"
#include "woody.h"
#include "libft.h"

void		sh_finish(t_shellcode *sh, t_shellcode_meta meta)
{
	uint32_t	val;

	ft_memcpy(sh->content + sh->off_entrypoint, &meta.entrypoint, 4);
	val = meta.section_text_offset - sh->off_vmaddr_text_ptr - 4;
	if (sh->off_vmaddr_text_ptr != 0)
		ft_memcpy(sh->content + sh->off_vmaddr_text_ptr, &val, 4);
	if (sh->off_vmaddr_text_len != 0)
		ft_memcpy(sh->content + sh->off_vmaddr_text_len, &meta.vmaddr_text_len, 4);
}
