/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:22:53 by wmari             #+#    #+#             */
/*   Updated: 2023/02/07 19:33:38 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	count_args(char ***block, int index, t_mimi *shell)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (block[index][i])
	{
		if (is_it_txt(block, index, i, shell))
			count++;
		i++;
	}
	return (count);
}

char	**create_args(char ***block, int index, t_mimi *shell)
{
	int		n;
	char	**args;
	int		i;

	n = count_args(block, index, shell);
	if (n == -1)
		return (NULL);
	args = ft_calloc(sizeof(char *), n + 1);
	if (!args)
		return (NULL);
	i = 0;
	n = 0;
	while (block[index][i])
	{
		if (is_it_txt(block, index, i, shell))
		{
			args[n] = ft_strdup(block[index][i]);
			if (!args[n])
				return (free_tab(args), NULL);
			n++;
		}
		i++;
	}
	return (args);
}
