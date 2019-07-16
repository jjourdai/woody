/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 11:59:07 by jjourdai          #+#    #+#             */
/*   Updated: 2016/11/05 12:26:53 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *s_cpy;
	size_t				i;
	void				*ptr;

	s_cpy = s;
	ptr = NULL;
	i = 0;
	while (i < n)
	{
		if (s_cpy[i] == (unsigned char)c)
		{
			ptr = (void*)&s_cpy[i];
			return (ptr);
		}
		i++;
	}
	return (NULL);
}
