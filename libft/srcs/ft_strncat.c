/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:18:53 by jjourdai          #+#    #+#             */
/*   Updated: 2017/02/20 10:32:43 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t j;

	j = 0;
	while (*dest)
		dest++;
	while (src[j] && j != n)
		*(dest++) = src[j++];
	*dest = '\0';
	return (dest);
}
