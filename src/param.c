/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polooo <polooo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:28:59 by jjourdai          #+#    #+#             */
/*   Updated: 2019/04/13 18:44:42 by polooo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"
#include "colors.h"

static struct params_getter options[] = {
	{"help", 'h', F_HELP, NULL, NULL, DUP_OFF},
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
				fprintf(stderr, GREEN_TEXT("nmap: Warning --%s have been previously stored you could have an undefined behaviour\n"), options[index].long_name);
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
					fprintf(stderr, GREEN_TEXT("nmap: Warning --%s have been previously stored you could have an undefined behaviour\n"), options[index].long_name);
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

t_list		*get_params(char **argv, int argc, uint32_t *flag)
{
	int 	i;
	t_list	*parameters;

	i = 0;
	parameters = NULL;
	while (++i < argc)
	{
		if (ft_strncmp(argv[i], "--", 2) == 0) {
			longname_opt(argv, flag, &i);
		} else if (argv[i][0] == '-') {
			shortname_opt(argv, flag, &i);	
		} else {
			list_push(&parameters, argv[i], strlen(argv[i]) + 1);
		//	__FATAL(UNDEFINED_PARAMETER, BINARY_NAME, argv[i]);
		}
	}
	return (parameters);
}

void	get_options(int argc, char **argv)
{
	ft_bzero(&env, sizeof(env));
	env.flag.filename = get_params(argv, argc, (uint32_t*)&env.flag.value);
	if (env.flag.value & F_HELP) {
		fprintf(stderr, GREEN_TEXT(USAGE) GREEN_TEXT(HELPER)); exit(EXIT_FAILURE);
	}
}
