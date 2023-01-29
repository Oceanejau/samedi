/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:16:19 by wmari             #+#    #+#             */
/*   Updated: 2023/01/23 11:50:18 by wmari            ###   ########.fr       */
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

int	ft_echo( char ***block, int index, t_mimi *shell)
{
	int	i;

	i = 1;
	if (block[index][1] && !ft_strncmp(block[index][1], "-n", 3))
		i = 2;
	if (!block[index][1])
		return (printf("\n"));
	while (block[index][i])
	{
		if (is_redir(block[index][i]))
			skip_redir(block[index], &i);
		else
		{
			printf("%s", block[index][i++]);
			if (block[index][i])
				printf(" ");
		}
	}
	if (block[index][1] && ft_strncmp(block[index][1], "-n", 3))
		printf("\n");
	free_block(block);
	free_list(shell);
	exit(EXIT_SUCCESS);
}

int	ft_soloecho(char ***block, int index)
{
	int	i;

	i = 1;
	if (block[index][1] && !ft_strncmp(block[index][1], "-n", 3))
		i = 2;
	if (!block[index][1])
		return (printf("\n"));
	while (block[index][i])
	{
		if (is_redir(block[index][i]))
			skip_redir(block[index], &i);
		else
		{
			printf("%s", block[index][i++]);
			if (block[index][i])
				printf(" ");
		}
	}
	if (block[index][1] && ft_strncmp(block[index][1], "-n", 3))
		printf("\n");
	return (0);
}
