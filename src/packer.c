#include "woody.h"

static void	write_data(t_elf64 *elf)
{
	int fd = __ASSERTI(-1, open("woody", O_WRONLY | O_TRUNC | O_CREAT, 0755), strerror(errno));
	write(fd, elf->mem, elf->len);
	close(fd);
}

static void	encrypt(uint64_t *addr, size_t length)
{
	switch (g_env.flag.cipher_type) {
		case XOR_32:
			xor(addr, length, g_env.key.xor32, X32);
			break;
		case XOR_16:
			xor(addr, length, g_env.key.xor16, X16);
			break;
		case XOR_8:
			xor(addr, length, g_env.key.xor8, X8);
			break;
		case RC5:
			rc5_encrypt(addr, length, g_env.key.rc5);
			break;
		case RC4:
			rc4_encrypt(addr, length, g_env.key.rc4);
			break;
	}
}

static void	inject_code(t_elf64 *elf)
{
	size_t			len;
	size_t			offset_real;
	void			*ptr;

	if (elf->target != NULL) {
		len = g_env.shellcode->len;
		if (elf->header->e_type == ET_DYN) {
			offset_real = elf->target->p_memsz + elf->target->p_offset;
		} else {
			offset_real = elf->target->p_memsz + elf->target->p_vaddr;
		}
		g_env.shellcode_meta.entrypoint = elf->header->e_entry - offset_real - len;
		g_env.shellcode_meta.section_text_offset = g_env.shellcode_meta.vmaddr_text_ptr - offset_real;
		elf->header->e_entry = offset_real;
		ptr = elf->mem + elf->target->p_memsz + elf->target->p_offset;
		sh_finish(g_env.shellcode, g_env.shellcode_meta);
		printf("Shellcode injected; len: %lu\n", g_env.shellcode->len);
		for (size_t i = 0; i < g_env.shellcode->len; ++i)
		{
			if (i != 0) printf(" ");
			printf("%02x", g_env.shellcode->content[i]);
		}
		printf("\n");
		encrypt(elf->mem + elf->offset_text, elf->len_text);
		ft_memcpy(ptr, g_env.shellcode->content, g_env.shellcode->len);
		elf->target->p_memsz += len;
		elf->target->p_filesz += len;
		elf->target->p_flags = elf->target->p_flags | PF_X;
	}
}

void		pack_this_file(char *filename)
{
	t_elf64		elf;

	elf64_loader(&elf, filename);
	browse_all_program_header(&elf);
	search_section_text_metadata(&elf);
	if (elf.target != NULL && elf.free_space >= g_env.shellcode->len)
		inject_code(&elf);
	else 
	{
		fprintf(stderr, "Want to inject shellcode of len: %lu\n", g_env.shellcode->len);
		fprintf(stderr, "Not enough space found for '%s'\n", filename);
		g_env.exit_code = WOODY_NO_SPACE;
	}
	write_data(&elf);
	munmap(elf.mem, elf.len);
}
