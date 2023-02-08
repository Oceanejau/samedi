/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_empty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:00:02 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 16:44:51 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	free_empty(char ***block, int *fbp, int *pipefd, t_mimi *shell)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close(*fbp);
	ft_putstr_fd("Command '' not found\n", STDERR_FILENO);
	free_block(block);
	free_list(shell);
	free_env(shell);
	free_tab(shell->env);
	free_sfd(shell->save_fd);
}

int	exec_empty(char ***block, int index, int *fbp, t_mimi *shell)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (free_block(block), return_error_pipe(block, fbp, shell));
	pid = fork();
	if (pid == -1)
		return (free_block(block), close(pipefd[0]),
			close(pipefd[1]), return_error_fork(block, fbp, shell));
	else if (pid == 0)
	{
		catch_signal(CHILD);
		if (create_file_redir(shell, index))
			return (return_error_redir(block, fbp, shell, pipefd));
		free_empty(block, fbp, pipefd, shell);
		exit(127);
	}
	else
		return (do_stuff_parent(pipefd, block, index, fbp));
}
