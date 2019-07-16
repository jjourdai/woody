/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:09:33 by jjourdai          #+#    #+#             */
/*   Updated: 2016/11/14 09:57:36 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			ptr = (char*)&s[i];
		else if (s[i + 1] == (unsigned char)c)
			ptr = (char*)&s[i + 1];
		i++;
	}
	return (ptr);
}

char	*ft_strrnchr(const char *s, int c, size_t max)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (s[i] && i < max)
	{
		if (s[i] == (unsigned char)c)
			ptr = (char*)&s[i];
		else if (s[i + 1] == (unsigned char)c)
			ptr = (char*)&s[i + 1];
		i++;
	}
	return (ptr);
}
