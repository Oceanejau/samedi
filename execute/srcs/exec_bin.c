/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:50:29 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 16:49:31 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	return_error_pipe(char ***block, int *fbp, t_mimi *shell)
{
	return (ft_putstr_fd("pipe: ", STDERR_FILENO),
		ft_putstr_fd(strerror(errno), STDERR_FILENO),
		return_error_redir(block, fbp, shell, NULL), 1);
}

int	return_error_fork(char ***block, int *fbp, t_mimi *shell)
{
	return (ft_putstr_fd("fork: ", STDERR_FILENO),
		ft_putstr_fd(strerror(errno), STDERR_FILENO),
		return_error_redir(block, fbp, shell, NULL), 1);
}

int	return_error_redir(char ***block, int *fbp, t_mimi *shell, int *pipefd)
{
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (count_pipe(shell))
	{
		free_block(block);
		free_env(shell);
		free_list(shell);
		free_sfd(shell->save_fd);
		close(*fbp);
		free_tab(shell->env);
		exit (1);
	}
	return (1);
}

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

int	exec_bin(char ***block, int index, int *fbp, t_mimi *shell)
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
		if (create_file_redir(shell, index))
			return (return_error_redir(block, fbp, shell, pipefd));
		if (do_stuff_child(block, index, fbp, pipefd))
			return_error_bin(block, fbp, shell);
		exec_child(block, index, fbp, shell);
		close(pipefd[1]);
		exit(127);
	}
	else
		do_stuff_parent(pipefd, block, index, fbp);
	return (0);
}
