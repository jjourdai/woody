#include "shellcode.h"

void	sh_free(t_shellcode *sh)
{
	munmap(sh, sh->len_mmap);
}
