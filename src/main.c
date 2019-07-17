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

void		pack_this_file(char *filename)
{
	int fd = __ASSERTI(-1, open(filename, O_RDONLY), "Open failed");
	struct stat buf;
	__ASSERTI(-1, fstat(fd, &buf), "fstat failed");
	void *mem = __ASSERT(MAP_FAILED, mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0), "mmap failed");

	Elf64_Ehdr *header;

	header = (Elf64_Ehdr *)mem;
	uint32_t magic = *(uint32_t*)mem;
	if (magic != ELF_MAGIC)
		__FATAL(UNKNOWN_MAGIC, BINARY_NAME, magic);
	uint8_t arch = header->e_ident[EI_CLASS];
	if (arch == ELFCLASS64) {
		printf("file class type := %s\n", elf_class[arch]);
		if (header->e_type == ET_EXEC || header->e_type == ET_DYN) {
			printf("file object type := %s\n", file_object_type[header->e_type]);
			printf("entry %lX\n", header->e_entry);
			printf("program header number %d\n", header->e_phnum);
		//	printf("offset first program hreader %lX\n", header->e_phoff);
			Elf64_Phdr *phdr = mem + header->e_phoff;
			for (int i = 0; i < header->e_phnum; i++) {
				if (phdr->p_type < COUNT_OF(program_header_type))
					printf("%s\n", program_header_type[phdr->p_type]);
				else 
					printf("Unknown Program header\n");
				phdr = (void*)phdr + header->e_phentsize;
			}
			printf("========================================\n");
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
}

int		main(int argc, char **argv)
{
	t_list *tmp;
	get_options(argc, argv);
//	init_sigaction();
		
	tmp = env.flag.filename;
	while (tmp) {
		printf("Current filename : %s\n", (char*)tmp->content);
		pack_this_file((char*)tmp->content);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
