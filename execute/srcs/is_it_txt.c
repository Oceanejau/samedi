/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_txt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:39:54 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 15:23:34 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_it_txt(char ***block, int index, int ind2, t_mimi *shell)
{
	t_list	*temp;
	int		comp_ind;
	int		comp_n;

	(void)block;
	temp = shell->list;
	comp_ind = 0;
	comp_n = 0;
	while (temp && comp_ind != index)
	{
		if (temp->type == PIPE)
			comp_ind++;
		temp = temp->next;
	}
	while (temp && comp_n != ind2)
	{
		temp = temp->next;
		comp_n++;
	}
	if (temp->type == TXT || temp->type == QUOTE)
		return (1);
	return (0);
}
