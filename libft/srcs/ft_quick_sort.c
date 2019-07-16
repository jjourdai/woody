/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 14:07:18 by jjourdai          #+#    #+#             */
/*   Updated: 2017/02/02 17:41:31 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap(int *tab, int a, int b)
{
	int tmp;

	tmp = tab[a];
	tab[a] = tab[b];
	tab[b] = tmp;
}

static int	partitionning(int *tab, int start, int end)
{
	int j;
	int i;
	int pivot;

	pivot = tab[start];
	i = start - 1;
	j = end + 1;
	while (1)
	{
		while (tab[i] < pivot)
			i++;
		while (tab[j] > pivot)
			j--;
		if (i >= j)
			return (j);
		else
			swap(tab, i, j);
	}
}

void		ft_quick_sort(int *tab, int start, int end)
{
	int pivot;

	if (start < end)
	{
		pivot = partitionning(tab, start, end);
		ft_putendl("dwdawda");
		ft_quick_sort(tab, start, pivot);
		ft_putendl("545454654");
		ft_quick_sort(tab, pivot + 1, end);
	}
}
