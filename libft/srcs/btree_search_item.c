/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 09:38:30 by jjourdai          #+#    #+#             */
/*   Updated: 2017/09/18 09:38:48 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*btree_search_item(t_btree *root, void *data_ref,
int (*cmpf)(void *, void*))
{
	if (root)
	{
		if ((*cmpf)(data_ref, root->item) < 0)
			return (btree_search_item(root->left, data_ref, cmpf));
		if ((*cmpf)(data_ref, root->item) == 0)
			return (root->item);
		if ((*cmpf)(data_ref, root->item) > 0)
			return (btree_search_item(root->right, data_ref, cmpf));
	}
	return (NULL);
}

int		btree_level_count(t_btree *root)
{
	int	node_number;
	int	number_left;
	int	number_right;

	node_number = 0;
	if (!root)
		return (node_number);
	node_number++;
	number_left = btree_level_count(root->left);
	number_right = btree_level_count(root->right);
	node_number += (number_left < number_right) ? number_right : number_left;
	return (node_number);
}
