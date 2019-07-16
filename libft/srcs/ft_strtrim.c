/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:27:41 by jjourdai          #+#    #+#             */
/*   Updated: 2018/02/13 12:07:47 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_without_space(char const *s)
{
	size_t	i;
	size_t	j;
	char	*last_c;
	char	*first_c;

	i = 0;
	first_c = 0;
	last_c = 0;
	while (s[i])
	{
		if (!(s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		{
			if (first_c == 0)
				first_c = (char*)&s[i];
			last_c = (char*)&s[i];
		}
		i++;
	}
	j = 0;
	while (&first_c[j] != last_c)
		j++;
	return (j);
}

char			*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen_without_space(s);
	str = ft_memalloc(sizeof(char) * (len + 2));
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	j = 0;
	while (j <= len)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
