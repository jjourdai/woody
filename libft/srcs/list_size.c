/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 18:37:51 by jjourdai          #+#    #+#             */
/*   Updated: 2017/02/20 10:23:17 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		list_size(t_list *begin_list)
{
	int		size;
	t_list	*tmp;

	if (!begin_list)
		return (0);
	size = 0;
	tmp = begin_list;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}
