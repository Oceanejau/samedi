/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:04:44 by wmari             #+#    #+#             */
/*   Updated: 2023/02/09 16:23:50 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	free_alloc_cd(char ***block, t_mimi *shell, char *save, char **args)
{
	int	i;

	i = count_pipe(shell);
	free(save);
	free_tab(args);
	if (i)
	{
		free_tab(shell->env);
		free_env(shell);
		free_list(shell);
		free_block(block);
		exit(0);
	}
	g_ret = 0;
	return (0);
}

int	nb_args(char **tab)
{
	int	n;

	n = 0;
	while (tab[n])
		n++;
	return (n);
}

int	return_error(char ***block, int *fbp, t_mimi *shell)
{
	ft_putstr_fd("Error, can't create arguments\n", STDERR_FILENO);
	if (count_pipe(shell))
	{
		free_block(block);
		close(*fbp);
		free_list(shell);
		free_tab(shell->env);
		free_env(shell);
		free_sfd(shell->save_fd);
		exit(1);
	}
	return (1);
}
