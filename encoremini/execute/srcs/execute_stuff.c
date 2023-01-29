/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:07:29 by wmari             #+#    #+#             */
/*   Updated: 2023/01/19 15:16:59 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static int	is_last_cmd(char ***block, int index)
{
	if (block[index + 1] == NULL)
		return (1);
	return (0);
}

static int	exec_pid0(char ***block, int index, int *fd_btw_pipe, int *pipefd)
{
	if (*fd_btw_pipe != -1)
		if (dup2(*fd_btw_pipe, STDIN_FILENO) == -1)
			return (-1);
	if (close(pipefd[0]) == -1)
		return (-1);
	if (block[index + 1])
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (-1);
	}
	else
		close(*fd_btw_pipe);
	return (0);
}

int	exec_parent(int *pipefd, char ***block, int index, int *fd_btw_pipe)
{
	signal(SIGINT, SIG_IGN);
	if (close(pipefd[1]) == -1)
		return (-1);
	if (block[index + 1])
	{
		if (dup2(pipefd[0], *fd_btw_pipe) == -1)
			return (-1);
	}	
	else
		close(*fd_btw_pipe);
	if (close(pipefd[0]) == -1)
		return (-1);
	return (0);
}

static int	execute_child(
		char ***block,
		int index,
		int *fd_btw_pipe,
		t_mimi *shell)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (!exec_pid0(block, index, fd_btw_pipe, pipefd))
		{
			if (is_last_cmd(block, index))
				shell->ret = exec_bin(block, index, shell);
			else
				exec_bin(block, index, shell);
		}
	}
	else
		exec_parent(pipefd, block, index, fd_btw_pipe);
	return (0);
}

int	execute_stuff(char ***block, int index, int *fd_btw_pipe, t_mimi *shell)
{
	int		ret;
	char	*cmd;

	cmd = find_cmd(block[index]);
	if (!cmd)
		return (/*perror("malloc"), errno*/1);
	if (builtin_finder(cmd) != -1)
	{
		if (is_last_cmd(block, index))
			shell->ret = exec_prebuiltin(block, index, fd_btw_pipe, shell);
		else
			exec_prebuiltin(block, index, fd_btw_pipe, shell);
	}
	else
	{
		ret = execute_child(block, index, fd_btw_pipe, shell);
		if (ret == -1)
			return (free(cmd), 1);
	}
	return (free(cmd), 0);
}
