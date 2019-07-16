/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_tab_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:37:30 by jjourdai          #+#    #+#             */
/*   Updated: 2017/03/29 15:48:08 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap_tab_int(int **tab, int i, int j)
{
	int tmp;

	tmp = *tab[i];
	*tab[i] = *tab[j];
	*tab[j] = tmp;
}

void	ft_swap_tab_char(char **tab, int i, int j)
{
	char *tmp;

	tmp = tab[i];
	tab[i] = tab[j];
	tab[j] = tmp;
}
