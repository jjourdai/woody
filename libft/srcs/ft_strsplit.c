/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 12:34:43 by jjourdai          #+#    #+#             */
/*   Updated: 2018/04/07 13:26:48 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define VRAI 1
#define FAUX 0

static int	ft_nb_word(const char *str, char c, int *size)
{
	int i;
	int nb_word;

	i = 0;
	nb_word = 0;
	while (str[i + 1])
	{
		if ((str[i] == c && str[i + 1] != c))
			nb_word++;
		i++;
	}
	if (str[0] && str[0] != c)
		nb_word++;
	*size = nb_word;
	return (nb_word);
}

static int	ft_caract_number(char *str, int i, char c)
{
	int count;

	count = 0;
	while (str[i] && str[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;
	int		size;

	if (!s || (tab = ft_memalloc(sizeof(char*) * \
		(ft_nb_word(s, c, &size) + 1))) == 0)
		return (NULL);
	i = 0;
	j = 0;
	while (size--)
	{
		while (s[i] && s[i] == c)
			i++;
		k = 0;
		tab[j] = ft_memalloc(sizeof(char) * \
				(ft_caract_number((char*)s, i, c) + 1));
		while (s[i] && s[i] != c)
			tab[j][k++] = s[i++];
		tab[j++][k] = '\0';
		i++;
	}
	tab[j] = 0;
	return (tab);
}
