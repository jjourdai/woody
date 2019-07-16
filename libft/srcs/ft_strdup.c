/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 12:54:16 by jjourdai          #+#    #+#             */
/*   Updated: 2017/09/14 14:01:05 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s_dup;
	size_t	i;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	s_dup = ft_memalloc(sizeof(char) * (size + 1));
	if (s_dup == NULL)
		return (0);
	i = 0;
	while (i < size + 1)
	{
		if (s[i])
			s_dup[i] = s[i];
		else
			s_dup[i] = '\0';
		i++;
	}
	return (s_dup);
}

char	*ft_strdup_without_char(const char *s, char c)
{
	char	*s_dup;
	size_t	i;
	size_t	j;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen_without_char(s, '\n');
	s_dup = ft_memalloc(sizeof(char) * (size + 1));
	if (s_dup == NULL)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
			s_dup[j++] = s[i];
		i++;
	}
	s_dup[j] = '\0';
	return (s_dup);
}
