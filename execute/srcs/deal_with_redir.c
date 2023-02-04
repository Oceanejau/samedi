/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:01:14 by wmari             #+#    #+#             */
/*   Updated: 2023/01/31 14:42:38 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	preroutine(char ***block, int index, t_mimi *shell)
{
	int		n;
	char	**args;

	args = create_args(block, index, shell, 0);
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

static int	is_there_a_file(t_mimi *shell, int index, int n)
{
	t_list	*temp;
	int		comp;

	comp = 0;
	temp = shell->list;
	while (temp && comp != index)
	{
		if (temp->type == PIPE)
			comp++;
		temp = temp->next;
	}
	comp = 0;
	while (temp && comp != n)
	{
		temp = temp->next;
		comp++;
	}
	if (temp->next && temp->next->type == TXT && temp->next->str)
		return (0);
	return (1);
}

int	deal_with_redir(char ***block, int index, int n, t_mimi *shell)
{
	if (!is_there_a_file(shell, index, n))
	{
		if (is_redir(block, index, n, shell) == INFILE)
			return (infile_modif(block[index][n + 1]));
		if (is_redir(block, index, n, shell) == D_INFILE)
			return (infile_modif(block[index][n + 1]));
		if (is_redir(block, index, n, shell) == OUTFILE)
			return (outfile_modif(block[index][n + 1]));
		if (is_redir(block, index, n, shell) == D_OUTFILE)
			return (outfile_dou_modif(block[index][n + 1]));
	}
	ft_putstr_fd("mimishell: redirection not found\n", STDERR_FILENO);
	return (1);
}
