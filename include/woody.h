/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polooo <polooo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:12:39 by jjourdai          #+#    #+#             */
/*   Updated: 2019/04/21 19:00:19 by polooo           ###   ########.fr       */
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

# define COUNT_OF(ptr) (sizeof(ptr) / sizeof((ptr)[0]))
# define OFFSETOF(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER)
# define USAGE BINARY_NAME" [--help] [--key HEXA_KEY] [--cipher CIPHER_TYPE] filename\n"

# define HELPER "--help, -h Print this help screen\n"\
		"--key, -k  give a key\n"\
		"--cipher, -c [xor32 | xor16 | xor8 | rc4 | rc5 | rc6]\n"\
			"xor32 is default\n"

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

# define TEXT_NAME	".text"

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

struct woody {
	struct {
		uint16_t	value;
		t_list		*filename;
		uint16_t	cipher_type;
		uint32_t	key;
	} flag;
	t_shellcode			*shellcode;
	t_shellcode_meta	shellcode_meta;
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
t_list	*get_params(char **argv, int argc, uint32_t *flag);
void	get_options(int argc, char **argv);

/* error.c */
void	handle_error(uint32_t line, char *file, t_bool fatal, uint32_t error_code,  ...);
int		x_int(int err, int res, char *str, char *file, int line);
void	*x_void(void *err, void *res, char *str, char *file, int line);

/* elf64_loader.c */

t_bool	elf64_loader(t_elf64 *elf, const char *filename);

// globals
struct woody			g_env;

extern const char		*file_object_type[];
extern const size_t		file_object_type_len;
extern const char		*program_header_type[];
extern const size_t		program_header_type_len;
extern const char		*section_header_type[];
extern const size_t		section_header_type_len;

#endif
