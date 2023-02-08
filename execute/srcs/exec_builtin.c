/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:58:58 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 16:50:18 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	return_error_bin(char ***block, int *fbp, t_mimi *shell)
{
	free_block(block);
	close(*fbp);
	free_env(shell);
	free_list(shell);
	free_sfd(shell->save_fd);
	free_tab(shell->env);
	exit(1);
}

int	exec_builtin(char ***block, int index, int *fbp, t_mimi *shell)
{
	int		pipefd[2];
	pid_t	pid;

	if (count_pipe(shell))
	{
		if (pipe(pipefd) == -1)
			return (free_block(block), return_error_pipe(block, fbp, shell));
		pid = fork();
		if (pid == -1)
			return (free_block(block), return_error_pipe(block, fbp, shell));
		else if (pid != 0)
			return (do_stuff_parent(pipefd, block, index, fbp));
		if (create_file_redir(shell, index))
			return (return_error_redir(block, fbp, shell, pipefd));
		if (do_stuff_child(block, index, fbp, pipefd))
			return_error_bin(block, fbp, shell);
		close(pipefd[1]);
		exec_built(block, index, shell, fbp);
		exit(127);
	}
	else
		return (exec_built(block, index, shell, fbp));
}
