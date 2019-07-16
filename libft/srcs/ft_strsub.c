/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:05:52 by jjourdai          #+#    #+#             */
/*   Updated: 2017/03/23 12:01:29 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	size_t			j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (NULL);
	str = ft_memalloc(sizeof(char) * (len + 1));
	while (s[i] && i < start)
		i++;
	while (j < len)
	{
		str[j++] = s[i++];
	}
	str[j] = '\0';
	return (str);
}
