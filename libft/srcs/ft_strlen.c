/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 12:51:09 by jjourdai          #+#    #+#             */
/*   Updated: 2018/04/07 16:53:19 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	const char *ptr;

	if (!s)
		return (0);
	ptr = s;
	while (*s)
		s++;
	return (s - ptr);
}

size_t	ft_strlen_without_char(const char *s, char c)
{
	size_t		i;
	size_t		size;

	if (!s)
		return (0);
	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] != c)
			size++;
		i++;
	}
	return (size);
}
