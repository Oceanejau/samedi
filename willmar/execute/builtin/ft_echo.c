/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:16:19 by wmari             #+#    #+#             */
/*   Updated: 2023/01/27 15:26:59 by wmari            ###   ########.fr       */
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

static int	deal_flags(char *str)
{
	int	i;
	//////int	flag;

	i = 0;
	////flag = 1;
	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while (str[i] && str[i] == 'n')
			i++;
	}
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

static int	resolution_empty(void)
{
	printf("\n");
	exit(0);
}

int	ft_echo(char ***block, int index, t_mimi *shell)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!block[index][i])
		resolution_empty();
	while (block[index][i] && deal_flags(block[index][i]))
		i++;
	if (i > 1)
		flag = 1;
	echo_comp(block, index, i, shell);
	if (flag == 0)
		printf("\n");
	free_block(block);
	free_list(shell);
	return (0);
}

int	ft_soloecho(char ***block, int index, t_mimi *shell)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!block[index][i])
		return (printf("\n"));
	while (block[index][i] && deal_flags(block[index][i]))
		i++;
	if (i > 1)
		flag = 1;
	echo_comp(block, index, i, shell);
	if (flag == 0)
		printf("\n");
	return (0);
}
