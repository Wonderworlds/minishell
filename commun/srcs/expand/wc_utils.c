/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 01:01:16 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/20 18:15:16 by fmauguin         ###   ########.fr       */
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

static t_wildcard	*new_wc(t_wildcard *mywc, char *found,
						size_t i, size_t i2)
{
	t_wildcard	*new;

	new = ft_calloc(1, sizeof(t_wildcard));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	new->dir_path = ft_strdup(mywc->dir_path);
	new->found = ft_strdup(found);
	new->prefix = ft_substr(found, 0, i2);
	if (mywc->suffix[i] == '\0')
		new->suffix = NULL;
	else
	{
		new->suffix = ft_strdup(&mywc->suffix[i]);
		if (!new->suffix)
		return (display_error("Error allocation\n", 0), NULL);
	}
	if (!new->dir_path || !new->prefix)
		return (display_error("Error allocation\n", 0), NULL);
	return (new);
}

static t_wildcard	*new_wc_path(t_wildcard *mywc, char *found,
						size_t i, size_t i2)
{
	t_wildcard	*new;
	char		*tmp;
	char		*tmp2;

	new = ft_calloc(1, sizeof(t_wildcard));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	tmp2 = ft_substr(found, 0 , i2 + i);
	if (!tmp2)
		return (display_error("Error allocation\n", 0), NULL);
	tmp = ft_join3(mywc->dir_path, "/", tmp2);
	free(tmp2);
	free(new->dir_path);
	new->dir_path = tmp;
	new->suffix = ft_strdup("");
	new->prefix = ft_strdup("");
	new->found = NULL;
	if (!new->dir_path || !new->prefix || !new->suffix)
		return (display_error("Error allocation\n", 0), NULL);
	if (update_wildcard(new, &mywc->suffix[i + 1]))
		return (NULL);
	return (new);
}

static t_wildcard	*prefix_suffix_content(t_wildcard *mywc,
						char *found, size_t i, size_t i2)
{
	size_t	k;

	if (mywc->suffix[i] == '*')
	{
		while (mywc->suffix[i] == '*')
			i++;
		if (mywc->suffix[i] == '\0' || mywc->suffix[i] == '/')
		{
			return (new_wc(mywc, found, i, ft_strlen(found)));
		}
	}
	if (mywc->suffix[i] == '/')
	{
		return (new_wc_path(mywc, found, i, i2));
	}
	while (found[i2])
	{
		k = 0;
		while (found[i2 + k] && mywc->suffix[i + k]
			&& mywc->suffix[i + k] == found[i2 + k])
			k++;
		if (mywc->suffix[i + k] == '*')
		{
			return (new_wc(mywc, found, i + k, i2 + k));
		}
		if (mywc->suffix[i + k] == '/' && found[i2 + k] == '\0')
		{
			return (new_wc_path(mywc, found, i + k, i2 + k));
		}
		if (mywc->suffix[i + k] == '\0' && found[i2 + k] == '\0')
			return (new_wc(mywc, found, i + k, i2 + k));
		i2++;
	}
	return (NULL);
}

t_wildcard	*prefix_suffix(t_wildcard *mywc, char *found)
{
	size_t		i;
	size_t		i2;

	i = 0;
	i2 = 0;
	while (mywc->prefix[i] && found[i2] && mywc->prefix[i] == found[i2])
	{
		i++;
		i2++;
	}
	if (mywc->prefix[i] != found[i2] && mywc->prefix[i])
		return (NULL);
	i = 0;
	return (prefix_suffix_content(mywc, found, i, i2));
}

t_wildcard	*init_wc(char *line)
{
	t_wildcard	*new;
	char		cwd_dir[DIR_BUFFER];

	new = ft_calloc(1, sizeof(t_wildcard *));
	if (!new)
		return (display_error("Error allocation\n", 0), NULL);
	if (line[0] == '/')
		new->dir_path = ft_strdup("");
	else
		new->dir_path = ft_strdup(getcwd(cwd_dir, DIR_BUFFER));
	new->found = NULL;
	new->suffix = ft_strdup("");
	new->prefix = ft_strdup("");
	if (!new->dir_path || !new->prefix || !new->suffix)
		return (display_error("Error allocation\n", 0), NULL);
	return (new);
}
