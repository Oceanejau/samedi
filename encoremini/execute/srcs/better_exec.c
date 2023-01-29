/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:11:55 by wmari             #+#    #+#             */
/*   Updated: 2023/01/19 12:04:32 by wmari            ###   ########.fr       */
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

int	better_exec(char ***block, t_mimi *shell)
{
	int		i;
	int		fd_btw_pipe;
	pid_t	wpid;

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
	i = 0;
	while (i < nb_cmd(block) && nb_cmd(block) >= 1)
	{
		wpid = wait(&(shell->ret));
	///	if (wpid)
		//	printf("signal\n");//a virer
		i++;
	}
	signal(SIGINT, SIG_DFL);
	return (free_block(block), 0);
}
