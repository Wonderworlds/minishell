/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 01:01:16 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/20 22:53:34 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "utils.h"

void	printf_wc(t_wildcard *mywc)
{
	if (mywc->dir_path)
		ft_printf("\tpath: %s\n", mywc->dir_path);
	if (mywc->found)
		ft_printf("\tfound: %s\n", mywc->found);
	if (mywc->prefix)
		ft_printf("\tprefix: %s\n", mywc->prefix);
	if (mywc->suffix)
		ft_printf("\tsuffix: %s\n\n", mywc->suffix);
}

static t_wildcard	*cpy_wc2(t_wildcard *wc, char *tmp, size_t i)
{
	t_wildcard	*new;

	new = ft_calloc(1, sizeof(t_wildcard));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	new->suffix = NULL;
	new->found = NULL;
	new->prefix = ft_strjoin(tmp, "/");
	if (i == 0)
		new->dir_path = ft_strdup("/");
	else
		new->dir_path = ft_substr(wc->dir_path, 0, i);
	if (!new->prefix || !new->dir_path)
	{
		del_node(new);
		return (display_error("Error allocation\n", 0), NULL);
	}
	return (new);
}

t_wildcard	*cpy_wc(t_wildcard *wc)
{
	t_wildcard	*new;
	char		*tmp;
	size_t		i;

	tmp = ft_strdup(ft_strrchr(wc->dir_path, '/') + 1);
	if (!tmp)
		return (display_error("Error allocation\n", 0), NULL);
	i = ft_strlen(wc->dir_path);
	while (--i >= 1)
		if (wc->dir_path[i] == '/')
			break ;
	new = cpy_wc2(wc, tmp, i);
	free(tmp);
	return (new);
}

t_wildcard	*init_wc(char *line)
{
	t_wildcard	*new;
	char		cwd_dir[DIR_BUFFER];

	new = ft_calloc(1, sizeof(t_wildcard));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	if (line[0] == '/')
		new->dir_path = ft_strdup("");
	else
	{
		new->dir_path = ft_strdup(getcwd(cwd_dir, DIR_BUFFER));
	}
	new->found = NULL;
	new->suffix = ft_strdup("");
	new->prefix = ft_strdup("");
	if (!new->dir_path || !new->prefix || !new->suffix)
	{
		del_node(new);
		return (display_error("Error allocation\n", 0), NULL);
	}
	return (new);
}