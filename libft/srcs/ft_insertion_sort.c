/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 13:54:55 by jjourdai          #+#    #+#             */
/*   Updated: 2017/03/14 14:24:16 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_insertion_sort(int *tab, size_t size)
{
	int i;
	int	j;
	int elem;

	i = 0;
	while (i < (int)size)
	{
		elem = tab[i];
		j = i;
		while (j > 0 && tab[j - 1] > elem)
		{
			tab[j] = tab[j - 1];
			j--;
		}
		tab[j] = elem;
		i++;
	}
}
