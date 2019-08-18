/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:12:39 by jjourdai          #+#    #+#             */
/*   Updated: 2019/08/18 13:15:23 by jpriou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <elf.h>

# include "libft.h"
# include "shellcode.h"
# include "encrypt.h"

# define COUNT_OF(ptr) (sizeof(ptr) / sizeof((ptr)[0]))
# define OFFSETOF(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER)
# define USAGE BINARY_NAME " [--help] [--key HEXA_KEY] [--cipher CIPHER_TYPE] filename\n"

# define HELPER "--help, -h Print this help screen\n"\
		"--key, -k  give a key\n"\
		"--cipher, -c [xor32 | xor16 | xor8 | rc4 | rc5 | rc6]\n"\
			"rc5 is default\n"

# define __FATAL(X, ...) handle_error(__LINE__, __FILE__, FATAL, X, __VA_ARGS__)
# define __ASSERTI(ERR_VALUE, RETURN_VALUE, STRING) x_int(ERR_VALUE, RETURN_VALUE, STRING, __FILE__, __LINE__)
# define __ASSERT(ERR_VALUE, RETURN_VALUE, STRING) x_void(ERR_VALUE, RETURN_VALUE, STRING, __FILE__, __LINE__)

# define BIT(n)			(1 << n)
# define SET(x, n)		(x | n)
# define UNSET(x, n)	(x & (~n))
# define ISSET(x, n)	(x & n)

# define BINARY_NAME "woody_woodpacker"
# define DEBUG 1
# define DUP_OFF 0
# define DUP_ON 1
# define FATAL 1
# define ELF_MAGIC 0x464c457f
# define RC5_KEY_SIZE 16
# define RC4_KEY_SIZE 16

# define DEFAULT_ALGO RC5

# define TEXT_NAME	".text"
# define XOR32_ASMFILE	"asm_files/xor32"
# define XOR16_ASMFILE	"asm_files/xor16"
# define XOR8_ASMFILE	"asm_files/xor8"
# define RC5_ASMFILE   "asm_files/rc5"
# define RC4_ASMFILE   "asm_files/rc4"

# define WOODY_OK		EXIT_SUCCESS
# define WOODY_FAIL		EXIT_FAILURE
# define WOODY_NO_SPACE	84

enum	options {
	F_HELP = (1 << 0),
	F_KEY = (1 << 1),
	F_CIPHER = (1 << 2),
};

enum	cipher_type {
	XOR_32 = 0,
	XOR_16,
	XOR_8,
	RC4,
	RC5,
	RC6,
};

enum	error {
	ERROR,
	UNDEFINED_PARAMETER,
	INVALID_SHORT_OPT,
	REQUIRED_ARG,
	INVALID_OPT,
	UNKNOWN_ARCH_TYPE,
	NOT_HANDLE_ARCH_32,
	UNKNOWN_MAGIC,
	ERR_FILE_OBJ,
	KEY_NOT_HEXA,
	KEY_TOO_LONG,
	UNKNOWN_CIPHER_TYPE,
	SECTION_TEXT_NOT_FOUND,
};

typedef struct parameters {
	char *str;
	enum options code;
}			t_parameters;

struct params_getter {
	char			*long_name;
	char			short_name;
	enum options	code;
	void	(*f)(char *, void *ptr);	
	void			*var;
	uint8_t			dup;
};

union key {
	uint8_t xor8;
	uint16_t xor16;
	uint32_t xor32;
	uint8_t rc5[RC5_KEY_SIZE]; 
	uint8_t rc4[RC4_KEY_SIZE]; 
};

struct woody {
	struct {
		char		*filename;
		char		*key_str;
		uint16_t	value;
		uint16_t	cipher_type;
	} flag;
	union key			key;
	char				*asm_file;
	t_shellcode			*shellcode;
	t_shellcode_meta	shellcode_meta;
	int					exit_code;
};

typedef struct	s_elf64
{
	void		*mem;
	size_t		len;
	Elf64_Ehdr	*header;
	Elf64_Phdr	*target;
	size_t		free_space;
	size_t		offset_text;
	size_t		len_text;
}				t_elf64;

/* params.c */
char	*get_params(char **argv, int argc, uint32_t *flag);
void	get_options(int argc, char **argv);

/* error.c */
void	handle_error(uint32_t line, char *file, t_bool fatal, uint32_t error_code,  ...);
int		x_int(int err, int res, char *str, char *file, int line);
void	*x_void(void *err, void *res, char *str, char *file, int line);

/* packer.c */
void	pack_this_file(char *filename);

/* elf64_loader.c */
t_bool	elf64_loader(t_elf64 *elf, const char *filename);

/* check_or_generate_key */
void	verify_key(void *data, size_t size);

/* elf64_dissect.c */
void    browse_all_program_header(t_elf64 *elf);
void    search_section_text_metadata(t_elf64 *elf);
Elf64_Shdr	*search_targeted_section(t_elf64 *elf, char *sect_name);


// globals
struct woody			g_env;

extern const char		*file_object_type[];
extern const size_t		file_object_type_len;
extern const char		*program_header_type[];
extern const size_t		program_header_type_len;
extern const char		*section_header_type[];
extern const size_t		section_header_type_len;

#endif
