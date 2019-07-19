#include "woody.h"
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

char shellcode[] = "\x50\x57\x56\x52\x51\x41\x50\x41\x51\x41\x52\x55\x48\x89\xe5\xe8\x0e\x00\x00\x00\x2e\x2e\x2e\x2e\x57\x4f\x4f\x44\x59\x2e\x2e\x2e\x2e\x0a\x5e\xbf\x01\x00\x00\x00\xba\x0e\x00\x00\x00\xb8\x01\x00\x00\x00\x0f\x05\x48\x89\xec\x5d\x41\x5a\x41\x59\x41\x58\x59\x5a\x5e\x5f\x58\xe9";

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
	printf("	p_memsz %lx\n", phdr->p_memsz);
	printf("	p_offset %lx\n", phdr->p_offset);
	if (fpt_load == NULL) {
		fpt_load = phdr;
	} else {
		spt_load = phdr;
		printf("Free space = '%lx' '%lu'\n", spt_load->p_offset - fpt_load->p_memsz, spt_load->p_offset - fpt_load->p_memsz);
		if (env.free_space < spt_load->p_offset - fpt_load->p_memsz) {
			env.free_space = spt_load->p_offset - fpt_load->p_memsz;
			env.target = fpt_load;
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
	uint32_t jmp_addr;
	size_t len = sizeof(shellcode) - 1 + sizeof(jmp_addr);
	if (env.target != NULL) {
		void *ptr = mem + env.target->p_memsz;
		jmp_addr = header->e_entry - env.target->p_memsz - sizeof(shellcode) - 1 - 2;
		/*
		   printf("new entry %lx\n", env.target->p_memsz);
		   printf("old entry %lx\n", header->e_entry);
		   printf("shellcode size %lx\n", sizeof(shellcode) - 1);
		   printf("jmp ? %x\n", (header->e_entry - env.target->p_memsz + sizeof(shellcode) - 1));
		   printf("test %x\n", header->e_entry - env.target->p_memsz - sizeof(shellcode) -1 + 2);
		   printf("jmp addr %x\n", jmp_addr);
		   printf("len shellcode %x\n", sizeof(shellcode) - 1);
		 */
		memcpy(ptr, shellcode, sizeof(shellcode) - 1);
		memcpy(ptr + sizeof(shellcode) - 1, &jmp_addr, sizeof(jmp_addr));
		header->e_entry = env.target->p_memsz;
		env.target->p_memsz += len;
		env.target->p_filesz += len;
	}
	write_data(mem, buf->st_size + len);
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
	if (env.target != NULL || env.free_space < sizeof(shellcode) - 1 + sizeof(uint32_t))
		inject_code(mem, header, &buf);
	else 
		fprintf(stderr, "Not enough space found for '%s'\n", filename);
	munmap(mem, buf.st_size);
	env.target = NULL;
}

#include "rc5.h"

int		main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "Usage: Need at least one filename\n");
		exit(EXIT_FAILURE);
	}
	bzero(&env, sizeof(env));
	t_list *tmp;
	get_options(argc, argv);
//	init_sigaction();

	/* pack all file got in argv  */
	tmp = env.flag.filename;
	while (tmp) {
		printf("Current filename : %s\n", (char*)tmp->content);
		pack_this_file((char*)tmp->content);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
