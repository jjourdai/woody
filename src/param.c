/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpriou <jpriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:28:59 by jjourdai          #+#    #+#             */
/*   Updated: 2019/07/29 17:40:24 by jpriou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"
#include "colors.h"

void	get_key(char *arg, void *var)
{
	if (str_is_hexa(arg) == 0) {
		__FATAL(KEY_NOT_HEXA, BINARY_NAME, arg);
	}
	*(char**)var = arg;
}


static char *cipher_type[] = {
	[XOR_32] = "xor32",
	[XOR_16] = "xor16",
	[XOR_8] = "xor8",
	[RC4] = "rc4",
	[RC5] = "rc5",
	[RC6] = "rc6",
};

void	get_cipher_type(char *arg, void *var)
{
	for (uint32_t i = 0; i < COUNT_OF(cipher_type); i++) {
		if (ft_strcmp(cipher_type[i], arg) == 0) {
			*((uint16_t*)var) = i;
			return ;
		}
	}
	__FATAL(UNKNOWN_CIPHER_TYPE, BINARY_NAME, arg);
}

static struct params_getter options[] = {
	{"help", 'h', F_HELP, NULL, NULL, DUP_OFF},
	{"key", 'k', F_KEY, get_key, &g_env.flag.key_str, DUP_OFF},
	{"cipher", 'c', F_CIPHER, get_cipher_type, &g_env.flag.cipher_type, DUP_OFF},
};

void	longname_opt(char **argv, uint32_t *flag, int *i)
{
	uint8_t index;
	char	*string;

	string = argv[*i] + 2;
	index = -1;
	while (++index < COUNT_OF(options))
	{
		if (ft_strcmp(options[index].long_name, string) == 0) {
			if ((*flag & options[index].code) == options[index].code && options[index].dup == DUP_OFF) {
				fprintf(stderr, "%swoody: Warning --%s have been previously stored you could have an undefined behaviour%s\n", get_color(COLOR_GREEN), options[index].long_name, get_reset());
			}
			*flag |= options[index].code;
			if (options[index].f != NULL) {
				if (argv[*i + 1] != NULL) {
					return options[index].f(argv[++(*i)], options[index].var);
				} else {
					__FATAL(REQUIRED_ARG, BINARY_NAME, options[index].long_name);
				}
			} else {
				return ;
			}
		}
	}
	__FATAL(INVALID_OPT, BINARY_NAME, string);
}

void	shortname_opt(char **argv, uint32_t *flag, int *i)
{
	int		j, flag_has_found;
	uint8_t index;
	char	c;

	j = 0;
	while ((c = argv[*i][++j]))
	{
		index = -1;
		flag_has_found = 0;
		while (++index < COUNT_OF(options))
		{
			if (options[index].short_name == c) {
				flag_has_found = 1;
				if ((*flag & options[index].code) == options[index].code && options[index].dup == DUP_OFF) {
					fprintf(stderr, "%swoody: Warning --%s have been previously stored you could have an undefined behaviour%s\n", get_color(COLOR_GREEN), options[index].long_name, get_reset());
				}
				*flag |= options[index].code;
				if (options[index].f != NULL) {
					if (argv[*i][j + 1] != '\0') {
						return options[index].f(&argv[*i][++j], options[index].var);
					} else if (argv[*i + 1] != NULL) {
						return options[index].f(argv[++(*i)], options[index].var);
					} else {
						__FATAL(REQUIRED_ARG, BINARY_NAME, options[index].long_name);
					}
				}
			}
		}
		if (flag_has_found != 1) {
			__FATAL(INVALID_SHORT_OPT, BINARY_NAME, c);
		}
	}
}

char		*get_params(char **argv, int argc, uint32_t *flag)
{
	int 	i;
	char	*filename;

	filename = NULL;
	i = 0;
	while (++i < argc)
	{
		if (ft_strncmp(argv[i], "--", 2) == 0) {
			longname_opt(argv, flag, &i);
		} else if (argv[i][0] == '-') {
			shortname_opt(argv, flag, &i);	
		} else {
			filename = argv[i];
		}
	}
	return (filename);
}

void	get_options(int argc, char **argv)
{
	g_env.flag.filename = get_params(argv, argc, (uint32_t*)&g_env.flag.value);
	if (g_env.flag.value & F_HELP) {
		fprintf(stderr, "%s%s%s%s", get_color(COLOR_GREEN), USAGE, HELPER, get_reset());
		exit(EXIT_SUCCESS);
	}
}
