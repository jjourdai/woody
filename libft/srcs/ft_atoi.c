/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 15:40:55 by jjourdai          #+#    #+#             */
/*   Updated: 2017/04/26 11:02:25 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *nptr)
{
	int n;
	int i;

	i = 0;
	while ((nptr[i] == '\n') || (nptr[i] == '\t') || (nptr[i] == '\v') ||
			(nptr[i] == ' ') || (nptr[i] == '\f') || (nptr[i] == '\r'))
		i++;
	if (nptr[i] == '-')
	{
		n = ft_atoi_u(nptr + ++i);
		n = n * -1;
	}
	else
	{
		if (nptr[i] == '+')
			i++;
		n = ft_atoi_u(nptr + i);
	}
	return (n);
}

unsigned int	ft_atoi_u(const char *nptr)
{
	int				i;
	unsigned int	nbr;

	nbr = 0;
	i = 0;
	while ((nptr[i] == '\n') || (nptr[i] == '\t') || (nptr[i] == '\v') ||
			(nptr[i] == ' ') || (nptr[i] == '\f') || (nptr[i] == '\r'))
		i++;
	i--;
	while (nptr[++i] && ft_isdigit(nptr[i]))
	{
		nbr = nbr * 10 + nptr[i] - 48;
	}
	return (nbr);
}
