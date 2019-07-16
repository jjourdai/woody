/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:53:19 by jjourdai          #+#    #+#             */
/*   Updated: 2016/11/14 10:52:34 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmps1;
	unsigned char	*tmps2;

	i = 0;
	tmps1 = (unsigned char*)s1;
	tmps2 = (unsigned char*)s2;
	while ((tmps1[i] || tmps2[i]) && i < n)
	{
		if (tmps1[i] == tmps2[i])
			i++;
		else
			return (tmps1[i] - tmps2[i]);
	}
	return (0);
}
