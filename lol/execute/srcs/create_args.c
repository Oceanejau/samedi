/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:11:15 by wmari             #+#    #+#             */
/*   Updated: 2023/01/25 17:15:49 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	return (0);
}

static int	count_args(char ***block, int index, t_mimi *shell)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (block[index][i])
	{
		if (is_redir(block, index, i, shell))
			skip_redir(block, index, &i, shell);
		else
		{
			i++;
			n++;
		}
	}
	return (n);
}

static char	**free_all(char **args, int n)
{
	if (args)
	{
		while (args[n])
			free(args[n++]);
	}
	free(args);
	return (NULL);
}

char	**create_args(char ***block, int index, t_mimi *shell)
{
	int		n;
	int		i;
	int		j;
	char	**args;

	n = count_args(block, index, shell);
	args = ft_calloc(sizeof(char *), n + 1);
	i = 0;
	j = 0;
	if (!args)
		return (NULL);
	while (i < n)
	{
		if (is_redir(block, index, i, shell))
			skip_redir(block, index, &i, shell);
		else
		{
			args[j] = ft_strdup(block[index][i]);
			if (!args[j])
				return (free_all(args, n));
			j++;
		}
		i++;
	}
	return (args);
}
