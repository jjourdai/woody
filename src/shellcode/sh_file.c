#include "shellcode.h"
#include "woody.h"
#include "libft.h"

static t_bool	search_text_section(t_elf64 *elf, void **text, size_t *len)
{
	Elf64_Shdr	*section;
	Elf64_Shdr	*shstrtab;
	char		*strtab;

	section = elf->mem + elf->header->e_shoff;
	shstrtab = section + elf->header->e_shstrndx;
	strtab = elf->mem + shstrtab->sh_offset;
	for (int i = 0; i < elf->header->e_shnum; i++) {
		if (ft_strncmp(strtab + section->sh_name, TEXT_NAME, ft_strlen(TEXT_NAME)) == 0)
		{
			*text = elf->mem + section->sh_offset;
			*len = section->sh_size;
			return (TRUE);
		}
		section = (void*)section + elf->header->e_shentsize;
	}
	return (FALSE);
}

t_bool			sh_file(t_shellcode *sh, const char *filepath)
{
	char		buffer[1025];
	t_elf64		elf;
	char		*text;
	size_t		len;

	ft_bzero(buffer, 1025);
	snprintf(buffer, 1024, "/usr/bin/nasm -f elf64 %s.s", filepath);
	if (system(buffer) != 0)
	{
		dprintf(2, "Compilation has failed somewhere\n");
		return (FALSE);
	}
	ft_bzero(buffer, 1025);
	snprintf(buffer, 1024, "%s.o", filepath);
	if (elf64_loader(&elf, buffer) == FALSE)
	{
		dprintf(2, "Load compiled file\n");
		return (FALSE);
	}
	if (search_text_section(&elf, (void **)&text, &len) == FALSE)
	{
		dprintf(2, "Unable to find txt section in compiled file\n");
		munmap(elf.mem, elf.len);
		return (FALSE);
	}
	for (size_t i = 0; i < len; ++i)
		sh->content[sh->len + i] = text[i] & 0xFF;
	sh->len += len;
	munmap(elf.mem, elf.len);
	return (TRUE);
}
