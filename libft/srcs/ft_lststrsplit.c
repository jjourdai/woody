/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststrsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 12:34:43 by jjourdai          #+#    #+#             */
/*   Updated: 2017/01/18 13:33:42 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define VRAI 1
#define FAUX 0

static size_t	ft_nb_word(const char *str, char c)
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

static size_t	ft_caract_number(char *str, size_t i, char c)
{
	size_t count;

	count = -1;
	while (str[i] && str[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

t_list			*ft_lststrsplit(char const *s, char c)
{
	t_list		*new;
	size_t		i;
	size_t		size;

	i = 0;
	new = NULL;
	if (!s)
		return (NULL);
	size = ft_nb_word(s, c);
	while (size--)
	{
		while (s[i] && s[i] == c)
			i++;
		list_push(&new, &s[i], ft_caract_number((char*)s, i, c));
		while (s[i] && s[i] != c)
			i++;
		i++;
	}
	return (new);
}
