/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_wait_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:42:36 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/23 18:03:12 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "astree.h"
#include "parser.h"
#include "minishell.h"
#include "g_minishell.h"

int	count_wait_tree(t_astree *root)
{
	if (root->cmd->type == CMD || root->cmd->type == AND
		|| root->cmd->type == OR)
		return (1);
	else if (root->cmd->type == PIPE)
		return (count_wait_tree(root->left) + count_wait_tree(root->right));
	return (0);
}