/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:50:22 by fmauguin          #+#    #+#             */
/*   Updated: 2022/07/08 17:13:34 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "utils.h"

static int	is_redirect_out(char *line, t_lxm *lxm, t_tokens *tokens, int *i)
{
	*i += 1;
	lxm->type = IO_OUT;
	if (line[*i] == '>')
	{
		*i += 1;
		lxm->type = IO_APP;
	}
	lxm->data = ft_strndup(line, *i);
	if (!lxm->data)
		return (error_alloc(), 1);
	tokens->size++;
	return (0);
}

static int	is_redirect_in(char *line, t_lxm *lxm, t_tokens *tokens, int *i)
{
	*i += 1;
	lxm->type = IO_IN;
	if (line[*i] == '<')
	{
		*i += 1;
		lxm->type = IO_HDOC;
	}
	lxm->data = ft_strndup(line, *i);
	if (!lxm->data)
		return (error_alloc(), 1);
	tokens->size++;
	return (0);
}

int	is_redirect(char *line, t_lxm *lxm, t_tokens *tokens)
{
	int	i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] == '>' || line[i] == '<')
	{
		if (tokens->size > 0 && (tokens->tokens[tokens->size - 1].type >= IO_IN
				&& tokens->tokens[tokens->size - 1].type <= IO_APP))
		{
			if (i > 0)
				return (error_syntax_str(line, i), -1);
			return (error_syntax(line[i]), -1);
		}
		if (line[i] == '>' && is_redirect_out(line, lxm, tokens, &i))
			return (-1);
		else if (line[i] == '<' && is_redirect_in(line, lxm, tokens, &i))
			return (-1);
	}
	return (i);
}
