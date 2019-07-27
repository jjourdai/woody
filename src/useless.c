#include "woody.h"

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
