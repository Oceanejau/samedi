/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:34:26 by wmari             #+#    #+#             */
/*   Updated: 2023/01/27 15:12:10 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	redir_or_not(char ***block, int index, int n, t_mimi *shell)
{
	int		comp_ind;
	int		comp_n;
	t_list	*temp;

	comp_ind = 0;
	comp_n = 0;
	(void)block;
	temp = shell->list;
	while (comp_ind != index)
	{
		if (temp->type == PIPE)
			comp_ind++;
		temp = temp->next;
	}
	while (comp_n != n)
	{
		temp = temp->next;
		comp_n++;
	}
	if (temp->type == TXT)
		return (0);
	return (1);
}

int	is_redir(char ***block, int index, int n, t_mimi *shell)
{
	if (ft_strncmp(">>", block[index][n], 3) == 0 && redir_or_not(block,
		index, n, shell))
		return (D_OUTFILE);
	if (ft_strncmp(">", block[index][n], 2) == 0 && redir_or_not(block,
		index, n, shell))
		return (OUTFILE);
	if (ft_strncmp("<<", block[index][n], 3) == 0 && redir_or_not(block,
		index, n, shell))
		return (D_INFILE);
	if (ft_strncmp("<", block[index][n], 2) == 0 && redir_or_not(block,
		index, n, shell))
		return (INFILE);
	return (NOT_REDIR);
}
