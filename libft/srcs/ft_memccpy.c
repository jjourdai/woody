/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:02:57 by jjourdai          #+#    #+#             */
/*   Updated: 2016/11/05 11:40:42 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*dest_cpy;
	const unsigned char	*src_cpy;
	size_t				i;

	i = 0;
	dest_cpy = dest;
	src_cpy = src;
	while (i < n)
	{
		dest_cpy[i] = src_cpy[i];
		if (dest_cpy[i] == (unsigned char)c)
		{
			i++;
			dest = &dest_cpy[i];
			return (dest);
		}
		i++;
	}
	return (NULL);
}
