/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:04:11 by wmari             #+#    #+#             */
/*   Updated: 2023/02/09 16:05:35 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	return_echo_child(
	char ***block,
	t_mimi *shell,
	int *fbp,
	char **args)
{
	int	i;

	i = count_pipe(shell);
	free_tab(args);
	if (i >= 2)
	{
		free_tab(shell->env);
		free_list(shell);
		free_env(shell);
		free_block(block);
		close(*fbp);
		free_sfd(shell->save_fd);
		exit(0);
	}
	g_ret = 0;
	return (0);
}

static int	deal_flags(char *str)
{
	int	i;

	i = 0;
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

int	ft_echo(char ***block, int index, t_mimi *shell, int *fbp)
{
	int		i;
	int		flag;
	char	**args;

	args = create_args(block, index, shell);
	if (!args)
		return (return_error(block, fbp, shell));
	if (!ft_strncmp(args[0], "", ft_strlen(args[0])))
		return (printf("\n"), return_echo_child(block, shell, fbp, args));
	i = 1;
	while (args[i] && deal_flags(args[i]))
		i++;
	flag = 0;
	if (i > 1)
		flag = 1;
	while (args[i])
	{
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return (return_echo_child(block, shell, fbp, args));
}
