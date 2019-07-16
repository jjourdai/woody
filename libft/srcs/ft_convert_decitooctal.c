/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_decitooctal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 14:29:08 by jjourdai          #+#    #+#             */
/*   Updated: 2016/12/29 16:28:15 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_convert_decitooctal(unsigned long long deci)
{
	unsigned long long octal;
	unsigned long long i;

	octal = 0;
	i = 1;
	while (deci != 0)
	{
		octal += (deci % 8) * i;
		deci /= 8;
		i *= 10;
	}
	return (octal);
}
