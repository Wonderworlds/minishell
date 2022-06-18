/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:19:37 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/18 16:44:59 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "astree.h"
#include "libft.h"
#include "utils.h"

static void	display_tree_content(char *prefix, t_astree *node, int is_left)
{
	const char	*e_type[] = {"CMD", "PIPE", "OR", "AND", "P_START", "P_END"};
	const char	*e_colors[] = {"\x1b[32m", "\x1b[33m", "\x1b[36m", "\x1b[34m",
		"\x1b[35m", "\x1b[31m"};
	int			type;

	ft_printf("%s", prefix);
	if (is_left)
		ft_printf("├──");
	else
		ft_printf("└──");
	type = node->cmd->type;
	if (type == CMD)
	{
		type = 0;
		if (node->cmd->cmd)
			ft_printf("%s%s\x1b[0m\n", e_colors[type], node->cmd->cmd->cmd[0]);
		else
			ft_printf("%s%s\x1b[0m\n", e_colors[type], node->cmd->cmd);
	}
	else
	{
		type -= 4;
		ft_printf("%s%s\x1b[0m\n", e_colors[type], e_type[type]);
	}
}

void	display_tree(char *prefix, t_astree *node, int is_left)
{
	char	*new_prefix;

	if (node)
	{
		display_tree_content(prefix, node, is_left);
		if (is_left)
		{
			new_prefix = ft_strjoin(prefix, "│   ");
			display_tree(new_prefix, node->left, 1);
			display_tree(new_prefix, node->right, 0);
		}
		else
		{
			new_prefix = ft_strjoin(prefix, "    ");
			display_tree(new_prefix, node->left, 1);
			display_tree(new_prefix, node->right, 0);
		}
		free(new_prefix);
	}
}
