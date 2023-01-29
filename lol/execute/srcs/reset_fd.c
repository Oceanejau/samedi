/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:30:21 by wmari             #+#    #+#             */
/*   Updated: 2023/01/25 14:04:42 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	set_fd(int *savefd)
{
	savefd[0] = dup(STDIN_FILENO);
	savefd[1] = dup(STDOUT_FILENO);
	savefd[2] = dup(STDERR_FILENO);
	return (0);
}

int	reset_fd(int *savefd)
{
	dup2(savefd[0], STDIN_FILENO);
	dup2(savefd[1], STDOUT_FILENO);
	dup2(savefd[2], STDERR_FILENO);
	return (0);
}

int	free_fd(int *savefd)
{
	close(savefd[0]);
	close(savefd[1]);
	close(savefd[2]);
	return (0);
}
