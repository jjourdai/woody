#ifndef SHELLCODE_H
# define SHELLCODE_H

# include <sys/mman.h>
# include <stddef.h>
# include <stdint.h>

# include "libft.h"

typedef struct	s_shellcode
{
	uint8_t		*content;
	size_t		len;
	size_t		len_mmap;
	t_bool		is_final;
}				t_shellcode;

t_shellcode		*sh_alloc(void);
void			sh_free(t_shellcode *sh);

size_t			sh_len_eff(t_shellcode *sh);

void			sh_regs_save(t_shellcode *sh);
void			sh_regs_recover(t_shellcode *sh);

void			sh_initframe(t_shellcode *sh);
void			sh_endframe(t_shellcode *sh);

void			sh_print(t_shellcode *sh, const char *str, uint8_t len);

void			sh_final_jump(t_shellcode *sh, uint32_t addr);

#endif
