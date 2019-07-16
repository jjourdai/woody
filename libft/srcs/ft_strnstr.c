/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:40:05 by jjourdai          #+#    #+#             */
/*   Updated: 2016/12/04 17:40:11 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	i_in_match;
	char	*ptr;

	i = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		i_in_match = i;
		ptr = (char*)&big[i];
		if (little[j] == big[i])
			while (little[j] == big[i] && big[i] && i < len)
			{
				if (little[j + 1] == '\0')
					return (ptr);
				i++;
				j++;
			}
		i = i_in_match;
		i++;
	}
	return (NULL);
}
