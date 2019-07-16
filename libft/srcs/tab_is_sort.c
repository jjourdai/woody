/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 13:15:02 by jjourdai          #+#    #+#             */
/*   Updated: 2019/01/30 16:47:15 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	tab_is_sort(int *tab, int lenght, int (*f)(int, int))
{
	int i;

	i = 0;
	while (i < lenght - 2)
	{
		if (f(tab[i], tab[i + 1]) < 0 && f(tab[i + 1], tab[i + 2]) > 0)
			return (0);
		else if (f(tab[i], tab[i + 1]) > 0 && f(tab[i + 1], tab[i + 2]) < 0)
			return (0);
		i++;
	}
	return (1);
}
