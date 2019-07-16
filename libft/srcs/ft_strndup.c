/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 12:54:16 by jjourdai          #+#    #+#             */
/*   Updated: 2018/02/12 09:30:05 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t size_max)
{
	char	*s_dup;
	size_t	i;
	size_t	size;

	if (s == NULL)
		return (0);
	size = ft_strlen(s);
	if (size > size_max)
		size = size_max;
	s_dup = ft_memalloc(sizeof(char) * (size + 1));
	i = 0;
	while (i < size && i < size_max)
	{
		if (s[i])
			s_dup[i] = s[i];
		i++;
	}
	s_dup[i] = '\0';
	return (s_dup);
}
