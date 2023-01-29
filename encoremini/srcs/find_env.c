/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:32:01 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 05:01:22 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*find_env(char *str, t_mimi *shell)
{
	char	*tmp;
	int		y;
	int		z;

	y = 0;
	while (str && shell->env[y] != NULL)
	{
		z = 0;
		while (str[z] == shell->env[y][z] && shell->env[y][z] != '=')
			z++;
		if (shell->env[y][z] == '=' && str[z] == '\0')
		{
			tmp = join(NULL, cpy_from_two_pos(shell->env[y], where_is_charly(shell->env[y],
						0, '=') + 1, ft_strlen(shell->env[y])));
			shell->s = ft_strlen(str) + 1;
			return (tmp);
		}
		y++;
	}
	return (NULL);
}
