/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_lookup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:10:07 by wmari             #+#    #+#             */
/*   Updated: 2023/01/29 21:51:41 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	builtin_finder(char *name)
{
	static char	*builtin_lookup[7];
	int			i;

	builtin_lookup[0] = "cd";
	builtin_lookup[1] = "pwd";
	builtin_lookup[2] = "exit";
	builtin_lookup[3] = "export";
	builtin_lookup[4] = "env";
	builtin_lookup[5] = "unset";
	builtin_lookup[6] = "echo";
	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(name, builtin_lookup[i], ft_strlen(name)) == 0 \
				&& ft_strlen(name) == ft_strlen(builtin_lookup[i]))
			return (i);
		i++;
	}
	return (-1);
}

static int	exec_pid0(char ***block, int index, int *fd_btw_pipe, int *pipefd)
{
	if (*fd_btw_pipe != -1)
		if (dup2(*fd_btw_pipe, STDIN_FILENO) == -1)
			return (perror("dup2"), 1);
	if (close(pipefd[0]) == -1)
		return (perror("close"), 1);
	if (block[index + 1])
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), -1);
	return (0);
}

int	exec_prebuiltin(char ***block, int index, int *fd_btw_pipe, t_mimi *shell)
{
	pid_t	pid;
	int		pipefd[2];

	if (nb_cmd(block) >= 2)
	{
		if (pipe(pipefd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), -1);
		if (pid == 0)
		{
			if (!exec_pid0(block, index, fd_btw_pipe, pipefd))
				exec_builtin(block, index, shell, fd_btw_pipe);
			close(pipefd[1]);
			free_all_built(block, shell, fd_btw_pipe);
			exit(g_ret);
		}
		else
			return (exec_parent(pipefd, block, index, fd_btw_pipe));
	}
	else
		return (exec_solobuiltin(block, index, shell, fd_btw_pipe));
	return (0);
}

int	exec_builtin(char ***block, int index, t_mimi *shell, int *fd_btw_pipe)
{
	char	*cmd;

	cmd = find_cmd(block, index, shell);
	last_cmd(block, index, fd_btw_pipe);
	if (preroutine(block, index, shell) == 1)
		return (1);
	if (builtin_finder(cmd) == 0)
		return (free(cmd), ft_cd(block, index, shell));
	if (builtin_finder(cmd) == 1)
		return (free(cmd), ft_pwd(block, index, shell));
	if (builtin_finder(cmd) == 2)
		return (free(cmd), ft_exit(block, index, shell, fd_btw_pipe));
	if (builtin_finder(cmd) == 3)
		return (free(cmd), ft_export(block, index, shell));
	if (builtin_finder(cmd) == 4)
		return (free(cmd), ft_env(block, index, shell));
	if (builtin_finder(cmd) == 5)
		return (free(cmd), ft_unset(block, index, shell));
	if (builtin_finder(cmd) == 6)
		return (free(cmd), ft_echo(block, index, shell));
	return (0);
}

int	exec_solobuiltin(char ***block, int index, t_mimi *shell, int *fd_btw_pipe)
{
	char	*cmd;

	cmd = find_cmd(block, index, shell);
	last_cmd(block, index, fd_btw_pipe);
	if (preroutine(block, index, shell) == 1)
		return (1);
	if (builtin_finder(cmd) == 0)
		return (free(cmd), ft_solocd(block, index, shell));
	if (builtin_finder(cmd) == 1)
		return (free(cmd), ft_solopwd(block, index));
	if (builtin_finder(cmd) == 2)
		return (free(cmd), ft_exit(block, index, shell, fd_btw_pipe));
	if (builtin_finder(cmd) == 3)
		return (free(cmd), ft_soloexport(block, index, shell));
	if (builtin_finder(cmd) == 4)
		return (free(cmd), ft_soloenv(block, index, shell));
	if (builtin_finder(cmd) == 5)
		return (free(cmd), ft_solounset(block, index, shell));
	if (builtin_finder(cmd) == 6)
		return (free(cmd), ft_soloecho(block, index, shell));
	return (0);
}
