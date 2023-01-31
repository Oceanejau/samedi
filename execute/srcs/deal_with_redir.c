/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:01:14 by wmari             #+#    #+#             */
/*   Updated: 2023/01/30 19:21:07 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	preroutine(char ***block, int index, t_mimi *shell)
{
	int		n;
	char	**args;

	args = create_args(block, index, shell);
	if (args == NULL)
		return (1);
	n = 0;
	while (block[index][n])
	{
		if (is_redir(block, index, n, shell))
			deal_with_redir(block, index, n, shell);
		n++;
	}
	free_args(args);
	return (0);
}

int	deal_with_redir(char ***block, int index, int n, t_mimi *shell)
{
	int	fd[2];

	if (is_redir(block, index, n, shell) == INFILE)
		return (infile_modif(block[index][n + 1], fd[0]));
	if (is_redir(block, index, n, shell) == D_INFILE)
		return (infile_modif(block[index][n + 1], fd[0]));
	if (is_redir(block, index, n, shell) == OUTFILE)
		return (outfile_modif(block[index][n + 1], fd[1]));
	if (is_redir(block, index, n, shell) == D_OUTFILE)
		return (outfile_dou_modif(block[index][n + 1], fd[1]));
	return (0);
}
