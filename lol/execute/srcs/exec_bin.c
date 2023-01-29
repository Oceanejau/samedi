/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:12:44 by wmari             #+#    #+#             */
/*   Updated: 2023/01/26 22:30:35 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	free_block(char ***block)
{
	int	i;
	int	j;

	i = 0;
	while (block[i])
	{
		j = 0;
		while (block[i][j])
		{
			free(block[i][j]);
			j++;
		}
		free(block[i][j]);
		free(block[i]);
		i++;
	}
	free(block[i]);
	free(block);
}

void	free_all_bin(
		char **str,
		t_mimi *shell,
		char ***block,
		char *cmd)
{
	int	n;

	n = 0;
	if (str)
	{
		while (str[n])
			free(str[n++]);
		free(str[n]);
		free(str);
	}
	if (cmd)
		free(cmd);
	free_list(shell);
	free_block(block);
	free_env(shell);
	free_envchar(shell);
	free_fd(shell->save_fd);
}

static void	redir_stuff(char ***block, int index, t_mimi *shell, char **args)
{
	int	n;

	n = -1;
	while (block[index][++n])
	{
		if (is_redir(block, index, n, shell))
		{
			if (deal_with_redir(block, index, n, shell))
			{
				free_all_bin(args, shell, block, NULL);
				exit(EXIT_FAILURE);
			}
		}
	}
}

int	exec_bin(char ***block, int index, t_mimi *shell, int *fd_btw_pipe)
{
	char	**args;
	char	*cmd;

	args = create_args(block, index, shell);
	if (args == NULL)
		return (-1);
	redir_stuff(block, index, shell, args);
	cmd = find_path(find_cmd(block, index, shell), shell);
	if (!ft_strncmp(cmd, ".", 1) || !ft_strncmp(cmd, "/", 1))
		execve(cmd, args, shell->env);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	close(*fd_btw_pipe);
	free_all_bin(args, shell, block, cmd);
	return (0);
}