
#include "woody.h"
#include "shellcode.h"
#include "encrypt.h"
#include "colors.h"

static void	search_free_space(t_elf64 *elf, Elf64_Phdr *phdr)
{
	static Elf64_Phdr *spt_load = NULL;
	static Elf64_Phdr *fpt_load = NULL;

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

	phdr = elf->mem + elf->header->e_phoff;
	for (int i = 0; i < elf->header->e_phnum; i++) {
		if (phdr->p_type == PT_LOAD)
		{
			search_free_space(elf, phdr);
			phdr->p_flags |= PF_W;
		}
		phdr = (void*)phdr + elf->header->e_phentsize;
	}
	printf("========================================\n");
}

Elf64_Shdr *search_targeted_section(t_elf64 *elf, char *sect_name)
{
	Elf64_Shdr *section = elf->mem + elf->header->e_shoff;
	Elf64_Shdr *shstrtab = section + elf->header->e_shstrndx;
	char *strtab = elf->mem + shstrtab->sh_offset;

	for (int i = 0; i < elf->header->e_shnum; i++) {
		if (ft_strncmp(strtab + section->sh_name, sect_name, ft_strlen(sect_name)) == 0)
			return section;
		section = (void*)section + elf->header->e_shentsize;
	}
	return NULL;
}

void	search_section_text_metadata(t_elf64 *elf)
{
	Elf64_Shdr *section;

	section = search_targeted_section(elf, TEXT_NAME);
	if (section == NULL)
		__FATAL(SECTION_TEXT_NOT_FOUND, BINARY_NAME, "Not found");
	g_env.shellcode_meta.vmaddr_text_ptr = section->sh_addr;
	g_env.shellcode_meta.vmaddr_text_len = section->sh_size;
	elf->offset_text = section->sh_offset;
	elf->len_text = section->sh_size;
}
