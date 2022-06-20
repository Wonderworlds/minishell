/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:56:54 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/20 16:50:34 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include <stdlib.h>
# include <dirent.h>
# include "libft.h"

# define DIR_BUFFER 4096

typedef struct s_wildcard
{
	char	*prefix;
	char	*suffix;
	char	*dir_path;
	char	*found;
}	t_wildcard;

int			strncmp_sep(char *s1, char *s2);
int			rec_wildcards(t_list **lst, t_list **new_lst);
int			update_wildcard(t_wildcard *mywc, char *line);

void		del_node(void *data);
void		ft_list_remove_if(t_list **begin_list, void *data_ref,
				int (*cmp)(), void (*free_fct)(void *));
void		print_lst2(void	*data);
void		printf_wc(t_wildcard *mywc);

t_list		*wildcards(char *line);

t_wildcard	*init_wc(void);
t_wildcard	*prefix_suffix(t_wildcard *mywc, char *found);

#endif