#include "woody.h"
// #include "colors.h"
#include "shellcode.h"
#include "encrypt.h"
#include "colors.h"

/*
void		signal_handler(int signal)
{

}

void		init_sigaction(void)
{
	struct sigaction sig = {
		.sa_handler = signal_handler,
	};
	sigaction(SIGALRM, &sig, NULL);
}
*/

Elf64_Off	remove_sections_header(t_elf64 *elf)
{
	Elf64_Off section_offset;
	
	section_offset = elf->header->e_shoff;
	elf->header->e_shoff = 0;
	elf->header->e_shentsize = 0;
	elf->header->e_shnum = 0;
	elf->header->e_shstrndx = SHN_UNDEF;

	return (section_offset);
}

void		write_data(t_elf64 *elf)
{
	// size_t	len;

	// len = remove_sections_header(elf);
	int fd = __ASSERTI(-1, open("woody", O_WRONLY | O_TRUNC | O_CREAT, 0755), strerror(errno));
	write(fd, elf->mem, elf->len);
	close(fd);
}

void		search_free_space(t_elf64 *elf, Elf64_Phdr *phdr)
{
	static Elf64_Phdr *spt_load = NULL;
	static Elf64_Phdr *fpt_load = NULL;

//	printf("	p_align %lx\n", phdr->p_align);
//	printf("	p_filesz %lx\n", phdr->p_filesz);
//	printf("	p_memsz %lx\n", phdr->p_memsz);
//	printf("	p_offset %lx\n", phdr->p_offset);
	if (fpt_load == NULL) {
		fpt_load = phdr;
	} else {
		spt_load = phdr;
		Elf64_Off space = spt_load->p_offset - (fpt_load->p_memsz + fpt_load->p_offset);
		printf("Free space = '%lx' '%lu'\n", space, space);
		if (elf->free_space < space) {
			elf->free_space = space;
			elf->target = fpt_load;
		}
		fpt_load = spt_load;
	}
}

void	browse_all_program_header(t_elf64 *elf)
{
	Elf64_Phdr	*phdr;

	/*
	printf("file object type := %s\n", file_object_type[elf->header->e_type]);
	printf("entry %lX\n", elf->header->e_entry);
	printf("program header number %d\n", elf->header->e_phnum);
	*/
	phdr = elf->mem + elf->header->e_phoff;
	for (int i = 0; i < elf->header->e_phnum; i++) {
		/*
		if (phdr->p_type < program_header_type_len)
			printf("%s\n", program_header_type[phdr->p_type]);
		else 
			printf("Unknown Program header\n");
		*/
		if (phdr->p_type == PT_LOAD)
		{
			search_free_space(elf, phdr);
			phdr->p_flags |= PF_W;
		}
		phdr = (void*)phdr + elf->header->e_phentsize;
	}
	printf("========================================\n");
}

void	browse_all_program_search_text(t_elf64 *elf)
{
	Elf64_Shdr *section = elf->mem + elf->header->e_shoff;
	Elf64_Shdr *shstrtab = section + elf->header->e_shstrndx;
	char *strtab = elf->mem + shstrtab->sh_offset;

	for (int i = 0; i < elf->header->e_shnum; i++) {
		if (ft_strncmp(strtab + section->sh_name, TEXT_NAME, ft_strlen(TEXT_NAME)) == 0)
		{
			// for (size_t i = 0; i < section->sh_size; ++i)
			// {
			// 	if (i != 0) printf(" ");
			// 	printf("%02x", (((char *)(elf->mem))[section->sh_offset + i] & 0xFF));
			// }
			// printf("\n");
			section->sh_flags |= SHF_WRITE; //TODO see later
			g_env.shellcode_meta.vmaddr_text_ptr = section->sh_addr;
			g_env.shellcode_meta.vmaddr_text_len = section->sh_size;
			elf->offset_text = section->sh_offset;
			elf->len_text = section->sh_size;
			return ;
		}
		section = (void*)section + elf->header->e_shentsize;
	}
}

void	display_section_header(t_elf64 *elf)
{
	printf("section number %d\n", elf->header->e_shnum); 
	Elf64_Shdr *section = elf->mem + elf->header->e_shoff;
	Elf64_Shdr *shstrtab = section + elf->header->e_shstrndx;
	char *strtab = elf->mem + shstrtab->sh_offset;
	for (int i = 0; i < elf->header->e_shnum; i++) {
		printf("Section name :'%20s	'", strtab + section->sh_name);
		if (section->sh_type < section_header_type_len)
			printf("type :'%s'\n", section_header_type[section->sh_type]);
		else 
			printf("type :'unknown'\n");
		section = (void*)section + elf->header->e_shentsize;
	}
	printf("========================================\n");

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
		xor32(elf->mem + elf->offset_text, elf->len_text, swap_bigendian_littleendian(g_env.key.xor32, 4));
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
	browse_all_program_search_text(&elf);
	// display_section_header(&elf);
	if (elf.target != NULL || elf.free_space < g_env.shellcode->len)
		inject_code(&elf);
	else 
		fprintf(stderr, "Not enough space found for '%s'\n", filename);
	write_data(&elf);
	munmap(elf.mem, elf.len);
}

void	atoi_key(void *data, size_t size, char *key)
{
	uint32_t	*cast = data;
	size_t		size_str;
	
	if ((size_str = ft_strlen(key)) > size * 2) {
		fprintf(stderr, "Warning !!! Given key to long it will be truncate\n"); 
	}
	size_str -= 8;
	int i = 0;
	do {
		cast[i] = ft_atoi_base(key + size_str, "0123456789ABCDEF");
		key[size_str] = 0;
		i++;
		size_str -= 8;
	} while (i < size / 4);
}

void	verify_key(void *data, size_t size)
{
	if (g_env.flag.value & F_KEY) {
		atoi_key(data, size, g_env.flag.key_str);
	} else {
		get_random_data(data, size);
	}
	printf(RED_TEXT("Encryption key : '0x"));
	int i = 0;
	do {
		printf(RED_TEXT("%hhx"), ((uint8_t*)data)[i]);
	} while (++i < size);
	printf(RED_TEXT("'\n"));
}

int		main(int argc, char **argv)
{
	ft_bzero(&g_env, sizeof(g_env));
	g_env.flag.cipher_type = XOR_32;
	get_options(argc, argv);
	if (g_env.flag.filename == NULL) {
		fprintf(stderr, USAGE);
		exit(EXIT_FAILURE);
	}	
	if (!(g_env.flag.value & F_CIPHER)) {
		g_env.flag.cipher_type = DEFAULT_ALGO;
	}

//	init_sigaction();
	g_env.shellcode = sh_alloc();
	sh_regs_save(g_env.shellcode);
	sh_initframe(g_env.shellcode);
	// sh_test(g_env.shellcode);
	// sh_test(g_env.shellcode);
	// sh_mprotect_text_writable(g_env.shellcode);
	// sh_mprotect_text_executable(g_env.shellcode);
	switch (g_env.flag.cipher_type) {
		case XOR_32:
			verify_key(&g_env.key.xor32, sizeof(g_env.key.xor32));
			sh_xor32(g_env.shellcode, g_env.key.xor32);
			break;
		case XOR_16:
			verify_key(&g_env.key.xor16, sizeof(g_env.key.xor16));
			printf("NOT HANDLED\n"); exit(EXIT_FAILURE);
			break;
		case XOR_8:
			verify_key(&g_env.key.xor8, sizeof(g_env.key.xor8));
			printf("NOT HANDLED\n"); exit(EXIT_FAILURE);
			break;
		case RC5:
			verify_key(&g_env.key.rc5, sizeof(g_env.key.rc5));
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
