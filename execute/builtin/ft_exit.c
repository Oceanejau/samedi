/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:33:08 by wmari             #+#    #+#             */
/*   Updated: 2023/01/27 15:51:32 by wmari            ###   ########.fr       */
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

static int	ret_value(unsigned long long nbr, int sign)
{
	unsigned long long	max;

	max = 922337203;
	max = (max * 10000000000) + 6854775808;
	if (nbr > 9223372036854775807 && sign >= 0)
		return (1);
	if (nbr > max && sign < 0)
		return (1);
	return (0);
}

static int	analyze_str(char *str)
{
	int					i;
	unsigned long long	nbr;
	int					sign;

	i = 0;
	nbr = 0;
	sign = 0;
	if (str[0] == '+' || str[0] == '-')
	{
		sign = -1;
		if (str[0] == '+')
			sign = 1;
		i++;
	}
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (1);
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	return (ret_value(nbr, sign));
}

int	ft_exit(char ***block, int index, t_mimi *shell, int *fd_btw_pipe)
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
			free_all_built(block, shell, fd_btw_pipe);
			exit(2);
		}
		i++;
	}
	if (i >= 3)
		return (printf("exit: too many arguments\n"), 1);
	free_block(block);
	free_all_built(block, shell, fd_btw_pipe);
	exit(j);
}
