/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:11:55 by wmari             #+#    #+#             */
/*   Updated: 2023/01/29 18:19:13 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "minishell.h"

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

static void	wait_child(char ***block)
{
	int	i;
	int status;
	int sign;

	i = 0;
	while (i < nb_cmd(block) && nb_cmd(block) >= 1)
	{
		wait(&status);
		if (WIFEXITED(status))
			g_ret = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sign = WTERMSIG(status);
			if (sign == SIGINT)
				ft_putstr_fd("\b\b\b", STDERR_FILENO);
			else
				ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			g_ret = sign + 128;
		}
		i++;
	}
}

int	better_exec(char ***block, t_mimi *shell)
{
	int		i;
	int		fd_btw_pipe;

	i = 0;
	fd_btw_pipe = dup(STDIN_FILENO);
	if (fd_btw_pipe == -1)
		return (perror("dup"), 1);
	while (block[i] && block[i][0])
	{
		if (execute_stuff(block, i, &fd_btw_pipe, shell) == -1)
			return (1);
		i++;
	}
	wait_child(block);
	catch_signal(PARENT);
	return (free_block(block), 0);
}
