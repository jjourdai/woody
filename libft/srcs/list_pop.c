/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:04:55 by jjourdai          #+#    #+#             */
/*   Updated: 2019/01/29 15:04:58 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*list_pop_front(t_list **list)
{
	t_list	*tmp;
	void	*content;

	if (list == NULL || *list == NULL)
		return (NULL);
	tmp = *list;
	*list = tmp->next;
	content = tmp->content;
	free(tmp);
	return (content);
}
