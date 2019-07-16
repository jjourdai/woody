/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:20:32 by jjourdai          #+#    #+#             */
/*   Updated: 2018/04/07 16:17:28 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;

	new = ft_memalloc(sizeof(char) * (ft_strlen(s2) + ft_strlen(s1) + 1));
	ft_strcpy(new, s1);
	ft_strcat(new, s2);
	return (new);
}

static void	ft_free(char *s1, char *s2)
{
	if (s2)
		free(s2);
	if (s1)
		free(s1);
}

char		*ft_strjoin_free(char *s1, char *s2, int free_s1_or_s2)
{
	char	*new;

	new = ft_memalloc(sizeof(char) * (ft_strlen(s2) + ft_strlen(s1) + 1));
	if (s2 && s1 && (s2[0] == '-' && s1[0] == '0'))
	{
		s2[0] = '0';
		s1[0] = '-';
	}
	else if (s1 && s2 && (s1[0] == '-' && s2[0] == '0'))
	{
		s1[0] = '0';
		s2[0] = '-';
	}
	ft_strcpy(new, s1);
	ft_strcat(new, s2);
	if (s1 && free_s1_or_s2 == 1)
		free(s1);
	if (s2 && free_s1_or_s2 == 2)
		free(s2);
	if (free_s1_or_s2 == 3)
		ft_free(s1, s2);
	return (new);
}

char		*ft_strjoin_size(char *s1, char *s2, int len_s1, int len_s2)
{
	char	*str;
	char	*str_init;
	int		i;

	i = -1;
	str = ft_memalloc(sizeof(char) * (len_s2 + len_s1 + 1));
	str_init = str;
	if (s1)
	{
		while (len_s1 != 0 && ++i < len_s1)
			*(str++) = *(s1++);
	}
	i = -1;
	if (s2)
	{
		while (len_s2 != 0 && ++i < len_s2)
			*(str++) = *(s2++);
	}
	*(str) = '\0';
	return (str_init);
}

char		*ft_strnjoin(char const *s1, char const *s2, size_t size)
{
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	new = ft_memalloc(sizeof(char) * (ft_strlen(s1) + 1 + size));
	ft_strcpy(new, s1);
	ft_strncat(new, s2, size);
	return (new);
}
