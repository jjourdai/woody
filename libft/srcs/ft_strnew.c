/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 12:05:24 by jjourdai          #+#    #+#             */
/*   Updated: 2018/04/07 17:32:14 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *str;

	str = ft_memalloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (0);
	ft_memset(str, 0, size + 1);
	return (str);
}
