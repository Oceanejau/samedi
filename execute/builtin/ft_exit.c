/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:41:49 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 16:31:09 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	return_exit(char ***block, char **args, t_mimi *shell, int *fbp)
{
	ft_putstr_fd("exit:", STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	free_block(block);
	free_tab(args);
	free_tab(shell->env);
	free_list(shell);
	free_env(shell);
	free_sfd(shell->save_fd);
	close(*fbp);
	exit(2);
}

static void	normal_exit(char ***block, char **args, t_mimi *shell, int *fbp)
{
	free_block(block);
	free_tab(args);
	free_tab(shell->env);
	free_list(shell);
	free_env(shell);
	free_sfd(shell->save_fd);
	close(*fbp);
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

int	ft_exit(char ***block, int index, t_mimi *shell, int *fbp)
{
	char	**args;
	int		i;
	int		j;

	args = create_args(block, index, shell);
	if (!args)
		return (return_error(block, fbp, shell));
	i = 1;
	j = 0;
	if (args[i])
		j = ft_atoi(args[i]);
	if (count_pipe(shell))
		printf("exit\n");
	while (args[i])
	{
		if (i >= 2)
			return (ft_putstr_fd("exit: too many arguments\n",
					STDERR_FILENO), free_tab(args), 1);
		if (analyze_str(args[i]))
			return_exit(block, args, shell, fbp);
		i++;
	}
	normal_exit(block, args, shell, fbp);
	exit(j);
}
