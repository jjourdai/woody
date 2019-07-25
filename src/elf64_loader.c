#include "woody.h"
#include "libft.h"

const char		*elf_class[] = {
	[ELFCLASSNONE] = "ELFCLASSNONE",
	[ELFCLASS32] = "ELFCLASS32",
	[ELFCLASS64] = "ELFCLASS64",
};

t_bool	elf64_loader(t_elf64 *elf, const char *filename)
{
	int			fd;
	struct stat	buf;
	void		*mem;
	Elf64_Ehdr	*hdr;
	uint8_t		arch;

	ft_bzero(elf, sizeof(*elf));
	fd = __ASSERTI(-1, open(filename, O_RDONLY), strerror(errno)); 
	__ASSERTI(-1, fstat(fd, &buf), strerror(errno)); 
	__ASSERT(MAP_FAILED, mem = mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0), strerror(errno)); 
	close(fd);
	hdr = (Elf64_Ehdr *)mem;
	if (*(uint32_t *)mem != ELF_MAGIC) {
		munmap(mem, buf.st_size);
		__FATAL(UNKNOWN_MAGIC, BINARY_NAME, *(uint32_t *)mem);
	}
	arch = hdr->e_ident[EI_CLASS];
	if (arch == ELFCLASS64) {
		if ((hdr->e_type == ET_EXEC || hdr->e_type == ET_DYN || hdr->e_type == ET_REL) == FALSE) {
			munmap(mem, buf.st_size);
			__FATAL(ERR_FILE_OBJ, BINARY_NAME, ((hdr->e_type < file_object_type_len) ?\
				file_object_type[hdr->e_type] : "UNKNOWN_TYPE corrupted file"));
		}
	}
	else if (arch == ELFCLASS32) {
		munmap(mem, buf.st_size);
		__FATAL(NOT_HANDLE_ARCH_32, BINARY_NAME, elf_class[arch]);
	}
	else {
		munmap(mem, buf.st_size);
		__FATAL(UNKNOWN_ARCH_TYPE, BINARY_NAME, "Unknown arch type");
	}
	elf->mem = mem;
	elf->len = buf.st_size;
	elf->header = hdr;
	return (TRUE);
}
