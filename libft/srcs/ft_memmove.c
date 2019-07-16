/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 11:40:55 by jjourdai          #+#    #+#             */
/*   Updated: 2016/11/09 10:20:01 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_cpy;
	const unsigned char	*src_cpy;
	size_t				i;

	dest_cpy = dest;
	src_cpy = src;
	i = -1;
	if (src_cpy < dest_cpy)
		while ((int)(--n) >= 0)
			dest_cpy[n] = src_cpy[n];
	else
		while (++i < n)
			dest_cpy[i] = src_cpy[i];
	return (dest);
}
