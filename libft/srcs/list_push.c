/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:51:35 by jjourdai          #+#    #+#             */
/*   Updated: 2019/01/31 15:48:41 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*list_push(t_list **alst, void const *content, size_t content_size)
{
	t_list *new;

	if ((new = ft_memalloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content != NULL)
	{
		new->content_size = content_size;
		new->content = ft_memalloc(content_size);
		ft_memcpy(new->content, content, content_size);
	}
	else
	{
		return (NULL);
	}
	new->next = *alst;
	*alst = new;
	return (new->content);
}

void	*list_push_back(t_list **alst, void const *content, size_t content_size)
{
	t_list *tmp;
	t_list *new;

	if ((new = ft_memalloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content != NULL)
	{
		new->content_size = content_size;
		new->content = ft_memalloc(content_size);
		ft_memcpy(new->content, content, content_size);
	}
	else
	{
		return (NULL);
	}
	tmp = *alst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*alst = new;
	return (new);
}

void	list_remove(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	tmp = *alst;
	while (tmp)
	{
		tmp = tmp->next;
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = tmp;
	}
	*alst = NULL;
}

void	remove_content(void *content, size_t content_size)
{
	if (content)
	{
		ft_bzero(content, content_size);
		free(content);
	}
}

void	list_reverse(t_list **lst)
{
	t_list *tmp;
	t_list *bef;
	t_list *nex;

	tmp = *lst;
	bef = NULL;
	if (tmp)
	{
		while (tmp)
		{
			nex = tmp->next;
			tmp->next = bef;
			bef = tmp;
			tmp = nex;
		}
		*lst = bef;
	}
}
