/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 12:34:43 by jjourdai          #+#    #+#             */
/*   Updated: 2018/12/12 15:37:57 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb_word(const char *str, char *charset, int *size)
{
	int i;
	int nb_word;

	i = 0;
	nb_word = 0;
	while (str[i + 1])
	{
		if (ft_strchr(charset, str[i]) && !ft_strchr(charset, str[i + 1]))
			nb_word++;
		i++;
	}
	if (str[0] && !ft_strchr(charset, str[0]))
		nb_word++;
	*size = nb_word;
	return (nb_word);
}

static int	ft_caract_number(const char *str, int i, char *charset)
{
	int j;
	int count;

	count = 0;
	while (str[i])
	{
		j = 0;
		while (charset[j])
		{
			if (str[i] == charset[j])
				return (count);
			j++;
		}
		count++;
		i++;
	}
	return (count);
}

char		**ft_split(const char *str, char *charset)
{
	char	**tab;
	int		i;
	int		j;
	int		k;
	int		size;

	if (!ft_nb_word(str, charset, &size))
		return (NULL);
	tab = ft_memalloc(sizeof(char*) * (size + 1));
	i = 0;
	j = 0;
	while (size--)
	{
		while (str[i] && ft_strchr(charset, str[i]))
			i++;
		k = 0;
		tab[j] = ft_memalloc(sizeof(char) *
				(ft_caract_number(str, i, charset) + 1));
		while (str[i] && !ft_strchr(charset, str[i]))
			tab[j][k++] = str[i++];
		tab[j++][k] = '\0';
	}
	tab[j] = 0;
	return (tab);
}
