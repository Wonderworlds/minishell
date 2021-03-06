/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 03:47:46 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/07 22:12:46 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "expand.h"
#include "libft.h"
#include "utils.h"

int	do_basic(char *cmd, t_list **lst_tmp)
{
	t_list	*index;
	t_list	*new;

	if (!cmd)
		return (error_alloc(), 1);
	index = *lst_tmp;
	if (!index)
	{
		new = ft_lstnew(cmd);
		if (!new)
			return (free(cmd), error_alloc(), 1);
		ft_lstadd_back(lst_tmp, new);
	}
	else
	{
		while (index)
		{
			if (strjoin_custom_lst(&(index->content), ft_strdup(cmd)))
				return (free(cmd), 1);
			index = index->next;
		}
		free(cmd);
	}
	return (0);
}

int	do_basic_lst(t_expand *expand)
{
	char	*tmp;
	size_t	next;

	next = to_next_index(&expand->line[expand->next]);
	tmp = ft_substr(&expand->line[expand->next], 0, next);
	if (!tmp)
		return (error_alloc(), 1);
	expand->next += next;
	return (do_basic(tmp, expand->tmp));
}

int	expand_loop(t_expand *expand)
{
	if (!expand->line[expand->next])
		return (validate_lst(expand));
	else if (expand->line[expand->next] == '\''
		|| expand->line[expand->next] == '"')
	{
		if (expand_quotes(expand))
			return (1);
	}
	else if (expand->line[expand->next] == '$')
	{
		if (expand_var(expand))
			return (1);
	}
	else
	{
		if (do_basic_lst(expand))
			return (1);
	}
	return (expand_loop(expand));
}
