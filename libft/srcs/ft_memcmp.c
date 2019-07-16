/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 12:26:58 by jjourdai          #+#    #+#             */
/*   Updated: 2017/03/29 15:47:39 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *s1_cpy;
	const unsigned char *s2_cpy;
	size_t				i;

	s1_cpy = s1;
	s2_cpy = s2;
	i = 0;
	while (i < n)
	{
		if (s1_cpy[i] != s2_cpy[i])
			return (s1_cpy[i] - s2_cpy[i]);
		i++;
	}
	return (0);
}

int		ft_memcmp_ignorecase(const void *s1, const void *s2, size_t n)
{
	const unsigned char *s1_cpy;
	const unsigned char *s2_cpy;
	size_t				i;
	unsigned char		car1;
	unsigned char		car2;

	s1_cpy = s1;
	s2_cpy = s2;
	i = 0;
	while (i < n)
	{
		car1 = s1_cpy[i];
		car2 = s2_cpy[i];
		if (car1 >= 65 && car1 <= 90)
			car1 += 32;
		if (car2 >= 65 && car2 <= 90)
			car2 += 32;
		if (car2 != car1)
			return (car1 - car2);
		i++;
	}
	return (0);
}
