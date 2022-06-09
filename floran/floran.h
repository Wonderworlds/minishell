/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floran.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:08:39 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/09 16:15:12 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLORAN_H
# define FLORAN_H

# include "minishell.h"
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define L_PATH 5

//parse
int		get_cmd(char **av, char **envp, t_list **l_cmd);

//free
void	free_node(void *data);
void	free_tab(char **tab);

//utils
char	*ft_join3(char *s1, char *s2, char *s3);

//debug
void	print_node(void *data);

#endif