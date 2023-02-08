/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:33:09 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 16:30:18 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	return_error_built(char ***block, t_mimi *shell, int *fbp)
{
	ft_putstr_fd("Error, can't create command (malloc)\n", STDERR_FILENO);
	if (count_pipe(shell))
	{
		free_block(block);
		close(*fbp);
		free_list(shell);
		free_tab(shell->env);
		free_env(shell);
		free_sfd(shell->save_fd);
		exit(1);
	}
	return (1);
}

int	exec_built(char ***block, int index, t_mimi *shell, int *fd_btw_pipe)
{
	char	*cmd;
	int		num;

	if (redir_stuff(shell, index))
		return (return_error_built(block, shell, fd_btw_pipe));
	cmd = find_cmd(shell, index);
	if (!cmd)
		return (return_error_built(block, shell, fd_btw_pipe));
	num = builtin_finder(cmd);
	if (num == 0)
		return (free(cmd), ft_cd(block, index, shell, fd_btw_pipe));
	if (num == 1)
		return (free(cmd), ft_pwd(block, index, shell, fd_btw_pipe));
	if (num == 2)
		return (free(cmd), ft_exit(block, index, shell, fd_btw_pipe));
	if (num == 3)
		return (free(cmd), ft_export(block, index, shell, fd_btw_pipe));
	if (num == 4)
		return (free(cmd), ft_env(block, index, shell, fd_btw_pipe));
	if (num == 5)
		return (free(cmd), ft_unset(block, index, shell, fd_btw_pipe));
	if (num == 6)
		return (free(cmd), ft_echo(block, index, shell, fd_btw_pipe));
	return (free(cmd), 0);
}
