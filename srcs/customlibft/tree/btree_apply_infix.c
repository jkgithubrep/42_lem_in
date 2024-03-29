/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_infix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:12:51 by apion             #+#    #+#             */
/*   Updated: 2019/06/10 21:13:50 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree_rb.h"

void	btree_apply_infix(t_rb_node *root, void *data, void (*fct)())
{
	if (!root || !fct)
		return ;
	if (root->left)
		btree_apply_infix(root->left, data, fct);
	if (data)
		fct(root, data);
	else
		fct(root);
	if (root->right)
		btree_apply_infix(root->right, data, fct);
}
