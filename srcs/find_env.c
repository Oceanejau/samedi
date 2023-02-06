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
	//printf("FIND========== %s\n", str);
	if (str == NULL)
	{
	//	free(str);
		return (NULL);
	}
	while (str && shell->env[y] != NULL)
	{
		z = 0;
		while (str[z] == shell->env[y][z] && shell->env[y][z] != '=')
			z++;
		if (shell->env[y][z] == '=' && str[z] == '\0')
		{
			tmp = cpy_from_two_pos(shell->env[y], where_charly(shell->env[y],
						0, '=') + 1, ft_strlenn(shell->env[y]));
			//shell->s = ft_strlenn(str) + 1;
		//	printf("STR de find = %s, tmp = %s\n\n",str, tmp);

			free(str);
			return (tmp);
		}
		y++;
	}
	shell->vent = ft_strlen(str);
//	printf("STR de find = %s\n\n",str);
	free(str);
	return (NULL);
}
