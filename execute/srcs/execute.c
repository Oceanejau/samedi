/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:03:24 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 16:27:44 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	count_pipe(t_mimi *shell)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = shell->list;
	while (temp)
	{
		if (temp->type == PIPE)
			i++;
		temp = temp->next;
	}
	return (i);
}

int	execute(t_mimi	*shell, char ***block)
{
	int	i;
	int	fd_btw_pipe;
	int	nb_pipe;

	i = 0;
	nb_pipe = count_pipe(shell);
	catch_signal(PARENT);
	fd_btw_pipe = dup(STDIN_FILENO);
	if (fd_btw_pipe == -1)
		return (free_block(block), ft_putstr_fd("dup: ", STDERR_FILENO),
			ft_putstr_fd(strerror(errno), STDERR_FILENO), 1);
	while (i <= nb_pipe)
		execute_stuff(block, i++, &fd_btw_pipe, shell);
	wait_children(block);
	return (free_block(block), close(fd_btw_pipe), 0);
}
