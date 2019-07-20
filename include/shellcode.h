#ifndef SHELLCODE_H
# define SHELLCODE_H

# include <sys/mman.h>
# include <stddef.h>
# include <stdint.h>

# include "libft.h"

// tab_textptr[0] is for the final jump

typedef struct	s_shellcode
{
	uint8_t		*content;
	size_t		len;
	size_t		len_mmap;
	size_t		tab_textptr[1];
}				t_shellcode;

t_shellcode		*sh_alloc(void);
void			sh_free(t_shellcode *sh);

void			sh_finish(t_shellcode *sh, uint32_t addr);

void			sh_regs_save(t_shellcode *sh);
void			sh_regs_recover(t_shellcode *sh);

void			sh_initframe(t_shellcode *sh);
void			sh_endframe(t_shellcode *sh);

void			sh_print(t_shellcode *sh, const char *str, uint8_t len);

void			sh_jump(t_shellcode *sh);

#endif
