/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 16:52:04 by jjourdai          #+#    #+#             */
/*   Updated: 2019/01/18 19:36:19 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	shift_data(char *data, int len, int size)
{
	int i;
	int	max;

	i = 0;
	max = len;
	while (--len)
	{
		data[i] = (i + size) > max ? 0 : data[i + size];
		++i;
	}
	data[i] = 0;
}
