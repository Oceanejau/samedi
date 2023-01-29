/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:43:28 by wmari             #+#    #+#             */
/*   Updated: 2023/01/29 14:51:14 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	echo_comp(char ***block, int index, int i, t_mimi *shell)
{
	while (block[index][i])
	{
		if (is_redir(block, index, i, shell))
			skip_redir(block, index, &i, shell);
		else
		{	
			printf("%s", block[index][i++]);
			if (block[index][i])
				printf(" ");
		}
	}
}

void	free_all_built(char ***block, t_mimi *shell, int *fd)
{
	(void)block;
	free_tab(shell->env);
	free_list(shell);
	free_env(shell);
	free_fd(shell->save_fd);
	close(*fd);
}
