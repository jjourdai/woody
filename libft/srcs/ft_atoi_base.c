/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 18:46:24 by jjourdai          #+#    #+#             */
/*   Updated: 2018/10/19 14:36:08 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	caract(char c, char *base)
{
	int i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

static int	error_base(char *base, int size)
{
	int		i;
	int		j;
	char	tmp[size];

	i = 0;
	if (base == 0)
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		tmp[i] = base[i];
		i++;
		j = 0;
		while (tmp[j])
		{
			if (tmp[j] == base[i])
				return (0);
			j++;
		}
	}
	return (1);
}

static int	error_str(char *base, char *str)
{
	int i;
	int j;

	i = 0;
	while ((str[i] == '\n') || (str[i] == '\t') || (str[i] == '\v') ||
		(str[i] == ' ') || (str[i] == '\f') || (str[i] == '\r') ||
		(str[i] == '+') || (str[i] == '-'))
		i++;
	while (str[i])
	{
		j = 0;
		while (base[j] != str[i])
		{
			if (base[j + 1] == '\0' && str[i] != base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int			ft_atoi_base(char *str, char *base)
{
	int i;
	int nbr;
	int negative;

	nbr = 0;
	negative = 0;
	i = 0;
	if (error_base(base, ft_strlen(base)) == 0 || error_str(base, str) == 0)
		return (0);
	while ((str[i] == '\n') || (str[i] == '\t') || (str[i] == '\v') ||
			(str[i] == ' ') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	while (str[i])
	{
		if (str[i] == '-')
			negative = 1;
		if (str[i] == '+' || str[i] == '-')
			i++;
		nbr = nbr * ft_strlen(base) + caract(str[i], base);
		i++;
	}
	if (negative == 1)
		return (-nbr);
	else
		return (nbr);
}
