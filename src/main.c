#include "woody.h"
// #include "colors.h"
#include "shellcode.h"

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

char *file_object_type[] = {
	[ET_NONE] = "ET_NONE",
	[ET_REL] = "ET_REL",
	[ET_EXEC] = "ET_EXEC",
	[ET_DYN] = "ET_DYN",
	[ET_CORE] = "ET_CORE",
};

char *elf_class[] = {
	[ELFCLASSNONE] = "ELFCLASSNONE",
	[ELFCLASS32] = "ELFCLASS32",
	[ELFCLASS64] = "ELFCLASS64",
};

char *program_header_type[] = {
	[PT_NULL] = "PT_NULL",
	[PT_LOAD] = "PT_LOAD",
	[PT_DYNAMIC] = "PT_DYNAMIC",
	[PT_INTERP] = "PT_INTERP",
	[PT_NOTE] = "PT_NOTE",
	[PT_SHLIB] = "PT_SHLIB",
	[PT_PHDR] = "PT_PHDR",
	//[PT_GNU_STACK] = "PT_GNU_EH_FRAME",
};

char *section_header_type[] = {
	[SHT_NULL] = "NULL",
	[SHT_PROGBITS] = "PROGBITS",
	[SHT_SYMTAB] = "SYMTAB",
	[SHT_STRTAB] = "STRTAB",
	[SHT_RELA] = "RELA",
	[SHT_HASH] = "HASH",
	[SHT_DYNAMIC] = "DYNAMIC",
	[SHT_NOTE] = "NOTE",
	[SHT_NOBITS] = "NOBITS",
	[SHT_REL] = "REL",
	[SHT_SHLIB] = "SHLIB",
	[SHT_DYNSYM] = "DYNSYN",
//	[SHT_LOPROC] = "LOPROC",
//	[SHT_HIPROC] = "HIPROC",
//	[SHT_LOUSER] = "LOUSER",
//	[SHT_HIUSER] = "HIUSER",
};

void		write_data(void *mem, size_t size)
{
	int fd = __ASSERTI(-1, open("packed", O_WRONLY | O_TRUNC | O_CREAT, 0755), "Open failed");
	write(fd, mem, size);
	close(fd);
}

void		search_free_space(Elf64_Phdr *phdr)
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
		if (g_env.free_space < space) {
			g_env.free_space = space;
			g_env.target = fpt_load;
		}
		fpt_load = spt_load;
	}
}

void	browse_all_program_header(void *mem, Elf64_Ehdr *header)
{
	printf("file object type := %s\n", file_object_type[header->e_type]);
	printf("entry %lX\n", header->e_entry);
	printf("program header number %d\n", header->e_phnum);
	Elf64_Phdr *phdr = mem + header->e_phoff;
	for (int i = 0; i < header->e_phnum; i++) {
		if (phdr->p_type < COUNT_OF(program_header_type))
			printf("%s\n", program_header_type[phdr->p_type]);
		else 
			printf("Unknown Program header\n");
		if (phdr->p_type == PT_LOAD)
			search_free_space(phdr);
		phdr = (void*)phdr + header->e_phentsize;
	}
	printf("========================================\n");
}

void	display_section_header(void *mem, Elf64_Ehdr *header)
{
	printf("section number %d\n", header->e_shnum); 
	Elf64_Shdr *section = mem + header->e_shoff;
	Elf64_Shdr *shstrtab = section + header->e_shstrndx;
	char *strtab = mem + shstrtab->sh_offset;
	for (int i = 0; i < header->e_shnum; i++) {
		printf("Section name :'%20s	'", strtab + section->sh_name);
		if (section->sh_type < COUNT_OF(section_header_type))
			printf("type :'%s'\n", section_header_type[section->sh_type]);
		else 
			printf("type :'unknown'\n");
		section = (void*)section + header->e_shentsize;
	}
	printf("========================================\n");

}

void	inject_code(void *mem, Elf64_Ehdr *header, struct stat *buf)
{
	uint32_t		jmp_addr;
	size_t			len;
	void			*ptr;

	if (g_env.target != NULL) {
		len = g_env.shellcode->len;
		jmp_addr = header->e_entry - (g_env.target->p_memsz + g_env.target->p_offset) - len;
		ptr = mem + g_env.target->p_memsz + g_env.target->p_offset;
		/*
		   printf("new entry %lx\n", g_env.target->p_memsz);
		   printf("old entry %lx\n", header->e_entry);
		   printf("shellcode size %lx\n", sizeof(shellcode) - 1);
		   printf("jmp ? %x\n", (header->e_entry - g_env.target->p_memsz + sizeof(shellcode) - 1));
		   printf("test %x\n", header->e_entry - g_env.target->p_memsz - sizeof(shellcode) -1 + 2);
		   printf("jmp addr %x\n", jmp_addr);
		   printf("len shellcode %x\n", sizeof(shellcode) - 1);
		 */
		
		sh_finish(g_env.shellcode, jmp_addr);
		memcpy(ptr, g_env.shellcode->content, g_env.shellcode->len);
		header->e_entry = g_env.target->p_memsz + g_env.target->p_offset;
		g_env.target->p_memsz += len;
		g_env.target->p_filesz += len;
		g_env.target->p_flags = g_env.target->p_flags | PF_X;
	}
	write_data(mem, buf->st_size);
}

void		pack_this_file(char *filename)
{
	int fd = __ASSERTI(-1, open(filename, O_RDONLY), "Open failed");
	struct stat buf;
	__ASSERTI(-1, fstat(fd, &buf), "fstat failed");
	void *mem = __ASSERT(MAP_FAILED, mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0), "mmap failed");
	close(fd);

	Elf64_Ehdr *header;

	header = (Elf64_Ehdr *)mem;
	uint32_t magic = *(uint32_t*)mem;
	if (magic != ELF_MAGIC)
		__FATAL(UNKNOWN_MAGIC, BINARY_NAME, magic);
	uint8_t arch = header->e_ident[EI_CLASS];
	if (arch == ELFCLASS64) {
		printf("file class type := %s\n", elf_class[arch]);
		if (header->e_type == ET_EXEC || header->e_type == ET_DYN) {
			browse_all_program_header(mem, header);
		//	display_section_header(mem, header);
		} else 
			if (header->e_type < COUNT_OF(file_object_type))
				__FATAL(ERR_FILE_OBJ, BINARY_NAME, file_object_type[header->e_type]);
			else 
				__FATAL(ERR_FILE_OBJ, BINARY_NAME, "UNKNOWN_TYPE corrupted file");
	} else if (arch == ELFCLASS32) {
		__FATAL(NOT_HANDLE_ARCH_32, BINARY_NAME, elf_class[arch]);
	} else {
		__FATAL(UNKNOWN_ARCH_TYPE, BINARY_NAME, "UNKNOWN");
	}
	if (g_env.target != NULL || g_env.free_space < g_env.shellcode->len)
		inject_code(mem, header, &buf);
	else 
		fprintf(stderr, "Not enough space found for '%s'\n", filename);
	munmap(mem, buf.st_size);
	g_env.target = NULL;
}

int		main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "Usage: Need at least one filename\n");
		exit(EXIT_FAILURE);
	}
	ft_bzero(&g_env, sizeof(g_env));
	t_list *tmp;
	get_options(argc, argv);
//	init_sigaction();

	g_env.shellcode = sh_alloc();
	sh_regs_save(g_env.shellcode);
	sh_initframe(g_env.shellcode);
	sh_print(g_env.shellcode, "....WOODY....\n", 14);
	sh_endframe(g_env.shellcode);
	sh_regs_recover(g_env.shellcode);
	sh_jump(g_env.shellcode);

	/* pack all file got in argv  */
	tmp = g_env.flag.filename;
	while (tmp) {
		printf("Current filename : %s\n", (char*)tmp->content);
		pack_this_file((char*)tmp->content);
		tmp = tmp->next;
	}
	sh_free(g_env.shellcode);
	return (EXIT_SUCCESS);
}
