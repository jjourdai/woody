#include "woody.h"
#include "shellcode.h"
#include "encrypt.h"
#include "colors.h"

void		write_data(t_elf64 *elf)
{
	int fd = __ASSERTI(-1, open("woody", O_WRONLY | O_TRUNC | O_CREAT, 0755), strerror(errno));
	write(fd, elf->mem, elf->len);
	close(fd);
}

void	encrypt(uint64_t *addr, size_t length)
{
	switch (g_env.flag.cipher_type) {
		case XOR_32:
			xor(addr, length, swap_bigendian_littleendian(g_env.key.xor32, X32), X32);
			break;
		case XOR_16:
			xor(addr, length, swap_bigendian_littleendian(g_env.key.xor16, X16), X16);
			break;
		case XOR_8:
			xor(addr, length, g_env.key.xor8, X8);
			break;
		case RC5:
			break;
	}
}

void	inject_code(t_elf64 *elf)
{
	size_t			len;
	void			*ptr;

	if (elf->target != NULL) {
		len = g_env.shellcode->len;
		if (elf->header->e_type == ET_DYN) {
			g_env.shellcode_meta.entrypoint = elf->header->e_entry - (elf->target->p_memsz + elf->target->p_offset) - len;
			elf->header->e_entry = elf->target->p_memsz + elf->target->p_offset;
			g_env.shellcode_meta.section_text_offset = g_env.shellcode_meta.vmaddr_text_ptr - (elf->target->p_memsz + elf->target->p_offset) - len;
		} else {
			g_env.shellcode_meta.entrypoint = elf->header->e_entry - (elf->target->p_memsz + elf->target->p_vaddr) - len;
			elf->header->e_entry = elf->target->p_memsz + elf->target->p_vaddr;
			g_env.shellcode_meta.section_text_offset = g_env.shellcode_meta.vmaddr_text_ptr - (elf->target->p_memsz + elf->target->p_vaddr) - len;
		}
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
	if (elf.target != NULL || elf.free_space < g_env.shellcode->len)
		inject_code(&elf);
	else 
		fprintf(stderr, "Not enough space found for '%s'\n", filename);
	write_data(&elf);
	munmap(elf.mem, elf.len);
}

int		main(int argc, char **argv)
{
	ft_bzero(&g_env, sizeof(g_env));
	get_options(argc, argv);
	if (g_env.flag.filename == NULL) {
		fprintf(stderr, USAGE);
		exit(EXIT_FAILURE);
	}	
	if (!(g_env.flag.value & F_CIPHER)) {
		g_env.flag.cipher_type = DEFAULT_ALGO;
	}

	g_env.shellcode = sh_alloc();
	sh_regs_save(g_env.shellcode);
	sh_initframe(g_env.shellcode);
	switch (g_env.flag.cipher_type) {
		case XOR_32:
			g_env.asm_file = XOR32_ASMFILE;
			verify_key(&g_env.key.xor32, sizeof(g_env.key.xor32));
			sh_xor(g_env.shellcode, g_env.key.xor32, X32);
			break;
		case XOR_16:
			g_env.asm_file = XOR16_ASMFILE;
			verify_key(&g_env.key.xor16, sizeof(g_env.key.xor16));
			sh_xor(g_env.shellcode, g_env.key.xor16, X16);
			break;
		case XOR_8:
			g_env.asm_file = XOR8_ASMFILE;
			verify_key(&g_env.key.xor8, sizeof(g_env.key.xor8));
			sh_xor(g_env.shellcode, g_env.key.xor8, X8);
			break;
		case RC5:
		//	verify_key(&g_env.key.rc5, sizeof(g_env.key.rc5));
			printf("NOT HANDLED\n"); exit(EXIT_FAILURE);
			break;
		default:
			printf("NOT HANDLED\n"); exit(EXIT_FAILURE);
			break;
	}
	sh_print(g_env.shellcode, "....WOODY....\n", 14);
	sh_endframe(g_env.shellcode);
	sh_regs_recover(g_env.shellcode);
	sh_jump(g_env.shellcode);

	printf("filename : %s\n", g_env.flag.filename);
	pack_this_file(g_env.flag.filename);
	sh_free(g_env.shellcode);
	return (EXIT_SUCCESS);
}
