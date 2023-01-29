/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:33:08 by wmari             #+#    #+#             */
/*   Updated: 2023/01/23 14:36:40 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static int	analyze_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (1);
		i++;
	}
	return (0);
}
static void	free_block(char ***block)
{
	int	i;
	int	j;

	i = 0;
	while (block[i])
	{
		j = 0;
		while (block[i][j])
			free(block[i][j++]);
		free(block[i][j]);
		free(block[i]);
		i++;
	}
	free(block[i]);
	free(block);
}

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	ft_exit(char ***block, int index, t_mimi *shell)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (block[index][1])
		j = ft_atoi(block[index][1]);
	if (nb_cmd(block) < 2)
		printf("exit\n");
	while (block[index][i])
	{
		if (analyze_str(block[index][i]))
		{
			printf("exit: %s: numeric argument required\n", block[index][i]);
			free_block(block);
			free_list(shell);
			free_tab(shell->env);
			exit(2);
		}
		i++;
	}
	if (i >= 3)
		return (printf("exit: too many arguments\n"), 1);
	free_block(block);
	free_tab(shell->env);
	free_list(shell);
	exit(j);
}
