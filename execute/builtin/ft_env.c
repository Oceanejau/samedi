/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:31:10 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 16:31:00 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	ft_env(char ***block, int index, t_mimi *shell, int *fbp)
{
	int	i;
	int	count_cmd;

	(void)index;
	i = 0;
	while (shell->env[i])
		printf("%s\n", shell->env[i++]);
	count_cmd = count_pipe(shell);
	if (count_cmd)
	{
		free_tab(shell->env);
		free_env(shell);
		free_list(shell);
		free_block(block);
		close(*fbp);
		free_sfd(shell->save_fd);
	}
	g_ret = 0;
	if (count_cmd >= 2)
		exit(0);
	return (0);
}
