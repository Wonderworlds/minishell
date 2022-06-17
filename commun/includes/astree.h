/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:45:19 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/17 23:45:51 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

# include "libft.h"
# include "parser.h"

typedef struct s_int_help
{
	int	i;
	int	min;
	int	max;
	int	is_open;
	int	is_done;
	int	depth;
}	t_int_help;

typedef struct s_astree
{
	t_parse			*cmd;
	struct s_astree	*left;
	struct s_astree	*right;
}	t_astree;

int			create_astree(t_astree **root, t_parse **parse);
void		astree_apply_prefix(t_astree *root);
t_astree	*create_node(t_parse *node);
t_int_help	*fill_t_int(t_parse **parse, int depth, int start);
int			run_tree(t_astree *node, t_parse **parse, t_int_help *i);

#endif