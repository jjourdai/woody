/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 09:37:01 by jjourdai          #+#    #+#             */
/*   Updated: 2018/04/07 13:31:35 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*btree_create_node(void *item)
{
	t_btree *node;

	if (!item)
		return (NULL);
	node = (t_btree*)ft_memalloc(sizeof(t_btree));
	node->item = item;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	btree_apply_prefix(t_btree *root, void (*applyf)(void*))
{
	if (!root)
		return ;
	(*applyf)(root);
	if (root->left)
		btree_apply_prefix(root->left, applyf);
	if (root->right)
		btree_apply_prefix(root->right, applyf);
}

void	btree_apply_infix(t_btree *root, void (*applyf)(void*))
{
	if (!root)
		return ;
	if (root->left)
		btree_apply_prefix(root->left, applyf);
	(*applyf)(root);
	if (root->right)
		btree_apply_prefix(root->right, applyf);
}

void	btree_apply_suffix(t_btree *root, void (*applyf)(void*))
{
	if (!root)
		return ;
	if (root->left)
		btree_apply_prefix(root->left, applyf);
	if (root->right)
		btree_apply_prefix(root->right, applyf);
	(*applyf)(root);
}

void	btree_insert_data(t_btree **root, void *item, int (cmpf)(void*, void*))
{
	t_btree *tmp;

	tmp = *root;
	if (!*root)
		(*root)->item = item;
	else if ((*cmpf)(tmp->item, item) >= 0)
		btree_insert_data(&tmp->right, item, cmpf);
	else if ((*cmpf)(tmp->item, item) < 0)
		btree_insert_data(&tmp->left, item, cmpf);
}
