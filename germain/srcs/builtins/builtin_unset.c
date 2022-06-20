/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:02:17 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/17 18:15:55 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "minishell.h"
#include "g_minishell.h"

/**
   Remove the given env_var.
*/

static int	unset_valid_format(char *name);

int	builtin_unset(int argc, char **argv, t_list **env)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (unset_valid_format(argv[i]) == 1)
			environment_remove(env, argv[i]);
		else
			ft_fprintf(2, "minishell: unset: `%s': not a valid identifier\n");
		i++;
	}
	return (0);
}

static int	unset_valid_format(char *name)
{
	int	i;

	i = 0;
	while (name[i] != '\0')
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
