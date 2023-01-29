/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:12:44 by wmari             #+#    #+#             */
/*   Updated: 2023/01/23 14:58:39 by wmari            ###   ########.fr       */
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

static void	free_all(
		char **str,
		t_mimi *shell,
		char ***block,
		char *cmd)
{
	int	n;

	n = 0;
	while (str[n])
		free(str[n++]);
	free(str[n]);
	free(str);
	free(cmd);
	free_list(shell);
	free_block(block);
}

int	exec_bin(char ***block, int index, t_mimi *shell)
{
	int		n;
	int		fd[2];
	char	**args;
	char	*cmd;

	signal(SIGQUIT, sig_quit_in_child);
	args = create_args(block[index]);
	if (args == NULL)
		return (-1);
	n = -1;
	while (block[index][++n])
	{
		if (is_redir(block[index][n]))
		{
			if (deal_with_redir(block[index], n, fd))
			{
				free_all(args, shell, block, NULL);
				exit(EXIT_FAILURE);
			}
		}
	}
	cmd = find_path(find_cmd(block[index]), shell);
	execve(cmd, args, shell->env);
	// printf("%s: command not found\n", cmd);
	perror(find_cmd(block[index]));
	free_all(args, shell, block, cmd);
	exit(127);
}
