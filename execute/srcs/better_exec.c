/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:11:55 by wmari             #+#    #+#             */
/*   Updated: 2023/01/31 17:18:34 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "minishell.h"

static void	free_block(char ***block)
{
	int	i;
	int	j;

	i = 0;
	if (block)
	{
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
}

static void	wait_child(char ***block)
{
	int	i;
	int	status;
	int	sign;

	i = 0;
	status = 0;
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
			else if (sign == SIGQUIT)
				ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			g_ret = sign + 128;
		}
		i++;
	}
}

static int	is_there_something(char ***block)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (block[i])
	{
		j = 0;
		while (block[i][j])
		{
			if (block[i][j] != NULL)
				count++;
			j++;
		}
		i++;
	}
	if (count)
		return (1);
	return (0);
}

static void	make_files(char ***block, t_mimi *shell)
{
	int	i;
	int	j;

	i = 0;
	while (block[i])
	{
		j = 0;
		while (block[i][j])
		{
			if (is_redir(block, i, j, shell))
				deal_with_redir(block, i, j, shell);
			j++;
		}
		i++;
	}
}

int	better_exec(char ***block, t_mimi *shell)
{
	int		i;
	int		fd_btw_pipe;

	i = 0;
	if (is_there_something(block))
	{
		catch_signal(PARENT);
		make_files(block, shell);
		fd_btw_pipe = dup(STDIN_FILENO);
		if (fd_btw_pipe == -1)
			return (perror("dup"), 1);
		while (block[i] && block[i][0])
		{
			execute_stuff(block, i, &fd_btw_pipe, shell);
			i++;
		}
		wait_child(block);
		return (free_block(block), 0);
	}
	return (free_block(block), 0);
}
