/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:32:51 by jjourdai          #+#    #+#             */
/*   Updated: 2018/09/12 12:33:19 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint64_t	swap_bigendian_littleendian(uint64_t number, size_t sizeoff)
{
	uint64_t	nb_swapped;
	int			i;
	int			j;
	int			i_max;

	if (sizeoff == 1)
		return ((number & 0xF0) >> 4 | (number & 0x0F) << 4);
	i = 0;
	j = sizeoff - 1;
	i_max = sizeoff / 2;
	nb_swapped = 0;
	while (i < i_max)
	{
		nb_swapped |= ((((size_t)0xFF << (8 * i)) & number) << (8 * (j - i)));
		nb_swapped |= ((((size_t)0xFF << (8 * j)) & number) >> (8 * (j - i)));
		i++;
		j--;
	}
	return (nb_swapped);
}
