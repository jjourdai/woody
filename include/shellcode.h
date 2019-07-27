#ifndef SHELLCODE_H
# define SHELLCODE_H

# include <sys/mman.h>
# include <stddef.h>
# include <stdint.h>

# include "libft.h"
# include "encrypt.h"

// tab_textptr[0] is for the final jump

typedef struct	s_shellcode
{
	uint8_t		*content;
	size_t		len;
	size_t		len_mmap;
	size_t		off_entrypoint;
	size_t		off_vmaddr_text_ptr[2];
	size_t		off_vmaddr_text_len[2];
}				t_shellcode;

typedef struct	s_shellcode_meta
{
	uint32_t	entrypoint;
	uint32_t	vmaddr_text_ptr;
	uint32_t	vmaddr_text_len;
	size_t		section_text_offset;
}				t_shellcode_meta;

t_shellcode		*sh_alloc(void);
void			sh_free(t_shellcode *sh);

void			sh_finish(t_shellcode *sh, t_shellcode_meta meta);

t_bool			sh_file(t_shellcode *sh, const char *filepath);

void			sh_regs_save(t_shellcode *sh);
void			sh_regs_recover(t_shellcode *sh);

void			sh_initframe(t_shellcode *sh);
void			sh_endframe(t_shellcode *sh);

void			sh_print(t_shellcode *sh, const char *str, uint8_t len);

void			sh_jump(t_shellcode *sh);

// void			sh_mprotect_text_writable(t_shellcode *sh);
// void			sh_mprotect_text_executable(t_shellcode *sh);

t_bool			sh_xor(t_shellcode *sh, uint32_t key, enum xor_size size);
t_bool			sh_rc5(t_shellcode *sh, uint8_t rc5[KEY_SIZE]);

#endif
