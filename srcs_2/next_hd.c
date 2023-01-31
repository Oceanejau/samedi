/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_hd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojauregu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 02:04:33 by ojauregu          #+#    #+#             */
/*   Updated: 2023/01/27 04:43:30 by ojauregu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**next_hd(t_mimi *shell, int x)
{
	t_list	*new;
	int		y;

	y = 0;
	new = shell->list;
	while (new != NULL)
	{
		if (new->type == 2 && new->str[0] == '<' && new->str[1] == '<')
			y++;
		if (x == y)
		{
			new = new->next;
			return (&new->str);
		}
		new = new->next;
	}
	return (NULL);
}
