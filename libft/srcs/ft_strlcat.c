/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:18:53 by jjourdai          #+#    #+#             */
/*   Updated: 2016/11/12 16:56:44 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t size_dst;

	i = 0;
	while (dst[i] && i < size)
		i++;
	size_dst = i;
	while (src[i - size_dst] && i < size - 1)
	{
		dst[i] = src[i - size_dst];
		i++;
	}
	if (size_dst < size)
		dst[i] = '\0';
	return (size_dst + ft_strlen(src));
}
