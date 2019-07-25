#include "shellcode.h"
#include "libft.h"
#include "woody.h"

#ifndef MAP_ANON
# define MAP_ANON 0x20
#endif

t_shellcode		*sh_alloc(void)
{
	t_shellcode		*ptr;
	size_t			len_page;

	len_page = 16 * getpagesize();
	if ((ptr = mmap(NULL, len_page, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, 0, 0)) == MAP_FAILED)
		return (NULL);
	ft_bzero(ptr, len_page);
	ptr->content = (uint8_t *)(ptr + 1);
	ptr->len = 0;
	ptr->len_mmap = len_page;
	return (ptr);
}
