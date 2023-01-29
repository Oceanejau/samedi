/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:01:14 by wmari             #+#    #+#             */
/*   Updated: 2022/12/22 15:11:27 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	preroutine(char **cmd_line)
{
	int		n;
	int		fd[2];
	char	**args;

	args = create_args(cmd_line);
	if (args == NULL)
		return (/*perror("malloc")*/1);//perror
	n = 0;
	while (cmd_line[n])
	{
		if (is_redir(cmd_line[n]))
			deal_with_redir(cmd_line, n, fd);
		n++;
	}
	free_args(args);
	return (0);
}

int	deal_with_redir(char **block, int n, int fd[2])
{
	if (is_redir(block[n]) == INFILE)
		return (infile_modif(block[n + 1], fd[0]));
	if (is_redir(block[n]) == D_INFILE)
		return (infile_modif(block[n + 1], fd[0]));
	if (is_redir(block[n]) == OUTFILE)
		return (outfile_modif(block[n + 1], fd[1]));
	if (is_redir(block[n]) == D_OUTFILE)
		return (outfile_dou_modif(block[n + 1], fd[1]));
	return (0);
}
