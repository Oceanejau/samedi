/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:14:21 by wmari             #+#    #+#             */
/*   Updated: 2023/02/07 19:33:38 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	wait_children(char ***block)
{
	int	i;
	int	status;
	int	sign;

	i = 0;
	status = 0;
	while (block[i] && block[i][0])
	{
		wait(&status);
		if (WIFEXITED(status))
			g_ret = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sign = WTERMSIG(status);
			if (sign == SIGINT)
				ft_putstr_fd("\n", STDERR_FILENO);
			else if (sign == SIGQUIT)
				ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			g_ret = sign + 128;
		}
		i++;
	}	
}
