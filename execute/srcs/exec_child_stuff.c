/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_stuff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:01:27 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 16:19:06 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	do_stuff_child(char ***block, int index, int *fbp, int *pipefd)
{
	catch_signal(CHILD);
	if (*fbp != -1)
		if (dup2(*fbp, STDIN_FILENO) == -1)
			return (ft_putstr_fd("dup2: ", STDERR_FILENO),
				ft_putstr_fd(strerror(errno), STDERR_FILENO),
				close(pipefd[0]), close(pipefd[1]), 1);
	close(pipefd[0]);
	if (block[index + 1])
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (ft_putstr_fd("dup2: ", STDERR_FILENO),
				ft_putstr_fd(strerror(errno), STDERR_FILENO),
				close(pipefd[1]), 1);
	}
	else
		close(*fbp);
	return (0);
}

int	exec_child(char ***block, int index, int *fbp, t_mimi *shell)
{
	char	**args;
	char	*cmd;
	char	*temp;

	args = create_args(block, index, shell);
	if (args == NULL)
		return (free_block(block), close(*fbp), free_list(shell),
			free_tab(shell->env), free_sfd(shell->save_fd),
			free_env(shell), 1);
	if (redir_stuff(shell, index))
		return (free_block(block), close(*fbp), free_list(shell),
			free_tab(shell->env), free_sfd(shell->save_fd),
			free_env(shell), free_tab(args), 1);
	temp = find_cmd(shell, index);
	cmd = find_path(temp, shell, 1);
	free(temp);
	if (!ft_strncmp(cmd, ".", 1) || !ft_strncmp(cmd, "/", 1))
		execve(cmd, args, shell->env);
	return (ft_putstr_fd(cmd, STDERR_FILENO),
		ft_putstr_fd(": command not found\n", STDERR_FILENO),
		free_block(block), close(*fbp), free_list(shell),
		free_tab(shell->env), free_sfd(shell->save_fd),
		free_env(shell), free_tab(args), free(cmd), 1);
}
