/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_lookup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:10:07 by wmari             #+#    #+#             */
/*   Updated: 2023/01/23 15:56:37 by wmari            ###   ########.fr       */
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
				exec_builtin(block, index, shell);
		}
		else
			return (exec_parent(pipefd, block, index, fd_btw_pipe));
	}
	else
		return (exec_solobuiltin(block, index, shell));
	return (0);
}

int	exec_builtin(char ***block, int index, t_mimi *shell)
{
	if (preroutine(block[index]) == 1)
		return (1);
	if (builtin_finder(find_cmd(block[index])) == 0)
		return (ft_cd(block, index, shell));
	if (builtin_finder(find_cmd(block[index])) == 1)
		return (ft_pwd(block, index, shell));
	if (builtin_finder(find_cmd(block[index])) == 2)
		return (ft_exit(block, index, shell));
	if (builtin_finder(find_cmd(block[index])) == 3)
		return (ft_export(block, index, shell));
	if (builtin_finder(find_cmd(block[index])) == 4)
		return (ft_env(block, index, shell));
	if (builtin_finder(find_cmd(block[index])) == 5)
		return (ft_unset(block, index, shell));
	if (builtin_finder(find_cmd(block[index])) == 6)
		return (ft_echo(block, index, shell));
	return (0);
}

int	exec_solobuiltin(char ***block, int index, t_mimi *shell)
{
	if (preroutine(block[index]) == 1)
		return (1);
	if (builtin_finder(find_cmd(block[index])) == 0)
		return (ft_solocd(block, index, shell));
	if (builtin_finder(find_cmd(block[index])) == 1)
		return (ft_solopwd(block, index));
	if (builtin_finder(find_cmd(block[index])) == 2)
		return (ft_exit(block, index, shell));
	if (builtin_finder(find_cmd(block[index])) == 3)
		return (ft_soloexport(block, index, shell));
	if (builtin_finder(find_cmd(block[index])) == 4)
		return (ft_soloenv(block, index, shell));
	if (builtin_finder(find_cmd(block[index])) == 5)
		return (ft_solounset(block, index, shell));
	if (builtin_finder(find_cmd(block[index])) == 6)
		return (ft_soloecho(block, index));
	return (0);
}
