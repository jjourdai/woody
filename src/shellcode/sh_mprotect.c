#include "shellcode.h"

// static void	sh_mprotect_abs(t_shellcode *sh, size_t index, uint8_t rights)
// {
// 	sh->content[sh->len + 0] = 0xb8; // mov rax
// 	sh->content[sh->len + 1] = 0x0a; // syscall mprotect
// 	sh->content[sh->len + 5] = 0x48; // 64 bit marker
// 	sh->content[sh->len + 6] = 0xbf; // mov rdi
// 	sh->off_vmaddr_text_ptr[index] = sh->len + 7;
// 	sh->content[sh->len + 15] = 0x48;
// 	sh->content[sh->len + 16] = 0xbe; // mov rsi
// 	sh->off_vmaddr_text_len[index] = sh->len + 17;
// 	sh->content[sh->len + 25] = 0xba; // mov rdx
// 	sh->content[sh->len + 26] = rights;
// 	sh->content[sh->len + 30] = 0x0f;
// 	sh->content[sh->len + 31] = 0x05; //syscall
// 	sh->len += 32;
// }

// void		sh_mprotect_text_writable(t_shellcode *sh)
// {
// 	sh_mprotect_abs(sh, 0, PROT_WRITE);	
// }

// void		sh_mprotect_text_executable(t_shellcode *sh)
// {
// 	sh_mprotect_abs(sh, 1, PROT_EXEC);	
// }
