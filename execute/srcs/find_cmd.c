/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmari <wmari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:33:56 by wmari             #+#    #+#             */
/*   Updated: 2023/02/08 15:22:26 by wmari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*find_cmd(t_mimi *shell, int index)
{
	int		count_pipe;
	t_list	*temp;

	temp = shell->list;
	count_pipe = 0;
	while (count_pipe != index)
	{
		if (temp->type == PIPE)
			count_pipe++;
		temp = temp->next;
	}
	while (temp)
	{
		if (temp->type == TXT || temp->type == QUOTE)
			return (ft_strdup(temp->str));
		temp = temp->next;
	}
	return (NULL);
}
