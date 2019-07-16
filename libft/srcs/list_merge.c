/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 16:08:42 by jjourdai          #+#    #+#             */
/*   Updated: 2017/02/20 10:27:35 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	list_merge(t_list **begin_list1, t_list *begin_list2)
{
	t_list *tmp;

	tmp = *begin_list1;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = begin_list2;
}

int		list_not_sort(t_list *lst, t_bool order)
{
	t_list	*tmp;
	int		i;

	i = 0;
	if (lst)
	{
		tmp = lst;
		while (tmp->next)
		{
			if (order == 1 && !((*(int*)tmp->content)
			< (*(int*)tmp->next->content)))
			{
				return (*((int*)tmp->content));
			}
			if (order == 0 && !((*(int*)tmp->content)
			> (*(int*)tmp->next->content)))
				return (*((int*)tmp->content));
			i++;
			tmp = tmp->next;
		}
	}
	return (0);
}

t_list	*list_map(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tmp;
	t_list *bef;
	t_list *new;

	if (!f)
		return (NULL);
	new = NULL;
	while (lst)
	{
		tmp = f(lst);
		if (!new)
		{
			new = tmp;
			bef = new;
			new->next = NULL;
		}
		else
		{
			new->next = tmp;
			tmp->next = NULL;
			new = new->next;
		}
		lst = lst->next;
	}
	return (bef);
}

void	list_iter(t_list *lst, void (*f)(t_list *elem))
{
	while (lst)
	{
		f(lst);
		lst = lst->next;
	}
}
