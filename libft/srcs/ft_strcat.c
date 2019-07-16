/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:13:54 by jjourdai          #+#    #+#             */
/*   Updated: 2017/03/29 15:54:38 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	if (!src)
		return (NULL);
	while (*dest)
		dest++;
	while (*(src))
		*(dest++) = *(src++);
	*dest = '\0';
	return (dest);
}
