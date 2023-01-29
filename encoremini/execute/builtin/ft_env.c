/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:46:28 by wmari             #+#    #+#             */
/*   Updated: 2022/12/29 14:50:56 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	free_block(char ***block)
{
	int	i;
	int	j;

	i = 0;
	while (block[i])
	{
		j = 0;
		while (block[i][j])
		{
			free(block[i][j]);
			j++;
		}
		free(block[i][j]);
		free(block[i]);
		i++;
	}
	free(block[i]);
	free(block);
}

int	ft_env(char ***block, int index, t_mimi *shell)
{
	int	i;

	(void)index;
	i = 0;
	while (shell->env[i])
		printf("%s\n", shell->env[i++]);
	free_block(block);
	free_list(shell);
	exit(EXIT_SUCCESS);
}

int	ft_soloenv(char ***block, int index, t_mimi *shell)
{
	int	i;

	(void)index;
	(void)block;
	i = 0;
	while (shell->env[i])
		printf("%s\n", shell->env[i++]);
	return (0);
}
