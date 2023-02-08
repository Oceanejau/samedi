/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:16:58 by wmari             #+#    #+#             */
/*   Updated: 2023/02/07 19:33:38 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	do_stuff_parent(int	*pipefd, char ***block, int index, int *fbp)
{
	catch_signal(PARENT);
	close(pipefd[1]);
	if (block[index + 1])
	{
		if (dup2(pipefd[0], *fbp) == -1)
			return (ft_putstr_fd("dup2: ", STDERR_FILENO),
				ft_putstr_fd(strerror(errno), STDERR_FILENO),
				close(pipefd[0]), 1);
	}
	else
		close(*fbp);
	close(pipefd[0]);
	return (0);
}
