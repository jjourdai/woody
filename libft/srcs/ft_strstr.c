/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:17:17 by jjourdai          #+#    #+#             */
/*   Updated: 2018/04/07 13:29:32 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	i_in_match;
	char	*ptr;

	i = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		i_in_match = i;
		ptr = (char*)&haystack[i];
		if (needle[j] == haystack[i])
			while (needle[j] == haystack[i] && haystack[i])
			{
				if (needle[j + 1] == '\0')
					return (ptr);
				j++;
				i++;
			}
		i = i_in_match;
		i++;
	}
	return (NULL);
}

char	*ft_strrstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	i_in_match;
	char	*ptr;
	char	*last_occur;

	i = -1;
	last_occur = NULL;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (haystack[++i])
	{
		j = -1;
		i_in_match = i;
		ptr = (char*)&haystack[i];
		if (needle[++j] == haystack[i])
			while (needle[j] == haystack[i] && haystack[i])
			{
				if (needle[j + 1] == '\0')
					last_occur = ptr;
				i++;
			}
		i = i_in_match;
	}
	return (last_occur);
}
