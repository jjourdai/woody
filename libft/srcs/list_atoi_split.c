/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_atoi_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:05:16 by jjourdai          #+#    #+#             */
/*   Updated: 2019/01/29 15:05:21 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define VRAI 1
#define FAUX 0

static size_t	nb_word(const char *str, char c)
{
	size_t i;
	size_t nb_word;

	i = 0;
	nb_word = 0;
	while (str[i + 1])
	{
		if ((str[i] == c && str[i + 1] != c))
			nb_word++;
		i++;
	}
	if (str[0] != c && str[0])
		nb_word++;
	return (nb_word);
}

static int		notdigit(long *nb, char *s, int i, t_list **new)
{
	if (((*nb = atoi(&s[i])) > INT_MAX || *nb < INT_MIN))
	{
		if (*new)
			list_remove(new, remove_content);
		return (0);
	}
	if ((!ft_isdigit(s[i]) && (s[i] != '-' && s[i] != '+'))
	|| (!ft_isdigit(s[i + 1]) && (s[i] == '-' && s[i] == '+')))
		return (0);
	i++;
	while (s[i] && s[i] != ' ')
	{
		if (!(ft_isdigit(s[i])))
			return (0);
		i++;
	}
	return (1);
}

t_list			*list_atoisplit(char const *s, char c)
{
	t_list		*new;
	size_t		i;
	size_t		size;
	long		nb;

	new = NULL;
	if (!s)
		return (NULL);
	size = nb_word(s, c);
	i = 0;
	while (size--)
	{
		while (s[i] && s[i] == c)
			i++;
		if (notdigit(&nb, (char*)s, i, &new) == 0)
			return (NULL);
		list_push(&new, &nb, sizeof(int));
		while (s[i] && s[i] != c)
			i++;
		i++;
	}
	return (new);
}
