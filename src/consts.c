#include "woody.h"

const char		*file_object_type[] = {
	[ET_NONE] = "ET_NONE",
	[ET_REL] = "ET_REL",
	[ET_EXEC] = "ET_EXEC",
	[ET_DYN] = "ET_DYN",
	[ET_CORE] = "ET_CORE",
};

const size_t	file_object_type_len = COUNT_OF(file_object_type);

const char		*elf_class[] = {
	[ELFCLASSNONE] = "ELFCLASSNONE",
	[ELFCLASS32] = "ELFCLASS32",
	[ELFCLASS64] = "ELFCLASS64",
};

const size_t	elf_class_len = COUNT_OF(elf_class);

const char		*program_header_type[] = {
	[PT_NULL] = "PT_NULL",
	[PT_LOAD] = "PT_LOAD",
	[PT_DYNAMIC] = "PT_DYNAMIC",
	[PT_INTERP] = "PT_INTERP",
	[PT_NOTE] = "PT_NOTE",
	[PT_SHLIB] = "PT_SHLIB",
	[PT_PHDR] = "PT_PHDR",
	//[PT_GNU_STACK] = "PT_GNU_EH_FRAME",
};

const size_t	program_header_type_len = COUNT_OF(program_header_type);

const char		*section_header_type[] = {
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

const size_t	section_header_type_len = COUNT_OF(section_header_type);