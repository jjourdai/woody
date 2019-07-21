#include "woody.h"
#include "libft.h"

t_bool	elf64_loader(t_elf64 *elf, const char *filename)
{
	int			fd;
	struct stat	buf;
	void		*mem;
	Elf64_Ehdr	*hdr;
	uint8_t		arch;

	ft_bzero(elf, sizeof(*elf));
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		dprintf(2, "Open failed\n");
		return (FALSE);
	}
	if (fstat(fd, &buf) < 0)
	{
		dprintf(2, "fstat failed\n");
		close(fd);
		return (FALSE);
	}
	if ((mem = mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		dprintf(2, "mmap failed\n");
		close(fd);
		return (FALSE);
	}
	close(fd);
	hdr = (Elf64_Ehdr *)mem;
	if (*(uint32_t *)mem != ELF_MAGIC)
	{
		dprintf(2, "Unknown magic number -- '%x'\n", *(uint32_t *)mem);
		munmap(mem, buf.st_size);
		return (FALSE);
	}
	arch = hdr->e_ident[EI_CLASS];
	if (arch == ELFCLASS64) {
		printf("file class type := %s\n", elf_class[arch]);
		if ((hdr->e_type == ET_EXEC || hdr->e_type == ET_DYN) == FALSE) {
			dprintf(2,
				"file object not supported need ET_DYN or ET_EXEC -- '%s'\n",
				(hdr->e_type < file_object_type_len) ? file_object_type[hdr->e_type] : "UNKNOWN_TYPE corrupted file");
			munmap(mem, buf.st_size);
			return (FALSE);
		}
	}
	else if (arch == ELFCLASS32) {
		dprintf(2, "Architecture X86_32 not handled\n");
		munmap(mem, buf.st_size);
		return (FALSE);
	}
	else {
		dprintf(2, "binary arch unknown -- '%x'\n", arch);
		munmap(mem, buf.st_size);
		return (FALSE);
	}
	elf->mem = mem;
	elf->len = buf.st_size;
	elf->header = hdr;
	return (TRUE);
}
