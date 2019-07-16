/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:48:50 by jjourdai          #+#    #+#             */
/*   Updated: 2017/03/20 12:41:47 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	if (!s)
		return (NULL);
	while (ptr[i])
	{
		if (ptr[i] == (unsigned char)c)
			return (&ptr[i]);
		else if (ptr[i + 1] == (unsigned char)c)
			return (&ptr[i + 1]);
		i++;
	}
	return (NULL);
}
